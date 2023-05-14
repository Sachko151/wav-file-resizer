#include "include/wav_operations.h"
FILE *open_wav_file_and_exit_if_error_encountered(char *filename, int silent_flag){
    log_function(silent_flag, open_wav_file_and_exit_if_error_encountered);
    FILE *input_file_pointer = fopen(filename, "rb");
    if (input_file_pointer == NULL) {
        fprintf(stderr, "Error opening input file\n");
        exit(EXIT_FAILURE);
    }
    log_function_parameter(silent_flag, filename,filename,s);
    log_function_return(silent_flag, open_wav_file_and_exit_if_error_encountered, input_file_pointer, p);
    return input_file_pointer;
}
void print_out_wav_file_metadata(wav_header_t wav_struct, int silent_flag){
    log_function(silent_flag, print_out_wav_file_metadata);
    printf("Chunk ID: %.4s\n", wav_struct.chunk_id);
    printf("Chunk Size: %u\n", (wav_struct.chunk_size+8)); //8 bytes not inclueded chunk id and chunk size
    printf("Format: %.4s\n", wav_struct.format);
    printf("Subchunk1 ID: %.4s\n", wav_struct.subchunk1_ID);
    printf("Subchunk1 Size: %u\n", wav_struct.subchunk1_size);
    printf("Audio Format: %hu\n", wav_struct.audio_format);
    printf("Number of Channels: %hu\n", wav_struct.num_channels);
    printf("Sample Rate: %u\n", wav_struct.sample_rate);
    printf("Byte Rate: %u\n", wav_struct.byte_rate);
    printf("Block Align: %hu\n", wav_struct.block_align);
    printf("Bits Per Sample: %hu\n", wav_struct.bits_per_sample);
    printf("Subchunk2 ID: %.4s\n", wav_struct.subchunk2_ID);
    printf("Subchunk2 Size: %u\n", wav_struct.subchunk2_size);
}
void print_out_wav_file_length_in_specified_format(wav_header_t wav_struct, int silent_flag){
    log_function(silent_flag, print_out_wav_file_length_in_specified_format);
    uint32_t length = return_length_of_wav_file_in_seconds(wav_struct,silent_flag);
    int hours = (int) length/3600;
    int easier_format = (int) length % 3600;
    int minutes = easier_format/60;
    int seconds = easier_format % 60;
    printf("The length of the file content is %.02d:%.02d:%.02d\n", hours,minutes,seconds);
}
void check_if_the_wav_file_has_correct_metadata_structure_and_exit_if_not(wav_header_t header, int silent_flag){
    log_function(silent_flag, check_if_the_wav_file_has_correct_metadata_structure_and_exit_if_not);
    if (strncmp(header.chunk_id, "RIFF", 4) != 0 ||
        strncmp(header.format, "WAVE", 4) != 0 ||
        strncmp(header.subchunk1_ID, "fmt ", 4) != 0 ||
        strncmp(header.subchunk2_ID, "data", 4) != 0) {
        fprintf(stderr, "Input file is not a WAV correct file\n");
        exit(EXIT_FAILURE);
    }
}
void extend_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, char *input_filename, 
char *output_filename, int silent_flag, long metadata_bytes){
    log_function(silent_flag, extend_the_wav_file_with_specified_duration_in_seconds);
    uint32_t num_samples = ((header.bits_per_sample / 2)*header.subchunk2_size) / (header.num_channels * header.bits_per_sample);
    if(header.num_channels == 2){
        num_samples*=2;
    }
    if(header.bits_per_sample == 24){
        num_samples -= header.sample_rate *2;
    }
    int32_t *data;
    uint32_t silence_len = (uint32_t)(duration * (header.sample_rate*header.num_channels)); // number of silence samples
    header.chunk_size = 36 + (num_samples + silence_len) * (header.bits_per_sample / 8);
    header.chunk_size+=metadata_bytes;
    header.subchunk2_size = ((num_samples / (header.bits_per_sample / 16)) + silence_len) * (header.bits_per_sample / 8);
    fwrite(&header, sizeof(wav_header_t), 1, output_file);
    write_memory_sequentially_extend(header, data, num_samples, silence_len, input_file, output_file, metadata_bytes);
    log_function_parameter(silent_flag, input_file, input_file, p);
    log_function_parameter(silent_flag, output_file, output_file, p);
    log_function_parameter(silent_flag, duration, duration, g);
    log_function_parameter(silent_flag, input_filename, input_filename, s);
    log_function_parameter(silent_flag, output_filename, output_filename, s);
    free_resources(input_file, output_file,silent_flag);
}
void trim_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, 
char *input_filename, char *output_filename, int silent_flag, long metadata_bytes){
    log_function(silent_flag, trim_the_wav_file_with_specified_duration_in_seconds);
    uint32_t length = header.subchunk2_size / (header.sample_rate * header.num_channels * header.bits_per_sample / 8);
    uint32_t dur = length - duration;
    int32_t *data;
    uint32_t num_samples = (uint32_t)(dur * ((header.sample_rate*(header.bits_per_sample / 16))*header.num_channels));
    header.chunk_size = 36 + (num_samples) * (header.bits_per_sample / 8);
    header.chunk_size+=metadata_bytes;
    header.subchunk2_size = ((num_samples / (header.bits_per_sample / 16))) * (header.bits_per_sample / 8);
    fwrite(&header, sizeof(wav_header_t), 1, output_file);
    num_samples = (uint32_t)(dur * ((header.sample_rate)*header.num_channels));
    write_memory_sequentially_trim(header, data, num_samples,input_file, output_file, metadata_bytes);
    log_function_parameter(silent_flag, input_file, input_file, p);
    log_function_parameter(silent_flag, output_file, output_file, p);
    log_function_parameter(silent_flag, duration, duration, g);
    log_function_parameter(silent_flag, input_filename, input_filename, s);
    log_function_parameter(silent_flag, output_filename, output_filename, s);
    free_resources(input_file, output_file, silent_flag);

}
uint32_t return_length_of_wav_file_in_seconds(wav_header_t wav_struct, int silent_flag){
    log_function(silent_flag, return_length_of_wav_file_in_seconds);
    log_function_return(silent_flag, return_length_of_wav_file_in_seconds, wav_struct.subchunk2_size / (wav_struct.sample_rate * wav_struct.num_channels * wav_struct.bits_per_sample / 8), u);
    return wav_struct.subchunk2_size / (wav_struct.sample_rate * wav_struct.num_channels * wav_struct.bits_per_sample / 8);
}
void free_resources(FILE *input_file, FILE *output_file, int silent_flag){
    log_function(silent_flag, free_resources);
    log_function_parameter(silent_flag, input_file, input_file, p);
    log_function_parameter(silent_flag, input_file, output_file, p);
    fclose(input_file);
    fclose(output_file);
}
void determine_whether_to_trim_extend_or_quit(uint32_t old_size, uint32_t new_size, wav_header_t header, FILE *input_file, 
                                            FILE *output_file, char *input_filename, char *output_filename, int silent_flag, long metadata_bytes){
    log_function(silent_flag, determine_whether_to_trim_extend_or_quit);
    int diff, display_diff;
    fseek(input_file, 44, SEEK_SET);
    change_duration_so_that_it_works_with_stereo(header, &new_size, &old_size, &diff, &display_diff);
    if(display_diff < 0){
        trim_the_wav_file_with_specified_duration_in_seconds(header, input_file, output_file, abs(diff), 
        input_filename, output_filename,silent_flag, metadata_bytes);
        printf("File successfully trimmed with %d seconds!\n", abs(display_diff));
    } else if(display_diff > 0){
        extend_the_wav_file_with_specified_duration_in_seconds(header, input_file, output_file, diff, 
        input_filename, output_filename,silent_flag, metadata_bytes);
        printf("File successfully extended with %d seconds!\n", display_diff);
    } else{
        printf("Nothing to do!\n");
    }
    log_function_parameter(silent_flag, old_size,old_size,u);
    log_function_parameter(silent_flag, new_size,new_size,u);
    log_function_parameter(silent_flag, input_file, input_file, p);
    log_function_parameter(silent_flag, output_file, output_file, p);
    log_function_parameter(silent_flag, input_filename, input_filename, s);
    log_function_parameter(silent_flag, output_filename, output_filename, s);
}
void read_the_metadata_for_the_wav_file(wav_header_t *header_metadata, FILE *input_file){
    fread(header_metadata, sizeof(wav_header_t), 1, input_file);//read the metadata
}
void change_duration_so_that_it_works_with_stereo(wav_header_t header, uint32_t *new_size, uint32_t *old_size, int *diff, int *display_diff){
    uint32_t display_new_size = *new_size;
    uint32_t display_old_size = *old_size;
    *display_diff = display_new_size - display_old_size;
    *diff = *new_size - *old_size;
}
void check_if_there_is_not_enough_memory_and_exit_if_there_isnt(void *ptr){
    if(ptr == NULL){
        fprintf(stderr, "No memory!");
        exit(EXIT_FAILURE);
    }
}
void check_if_new_size_is_zero_and_exit_if_true(uint32_t new_size){
    if(!new_size){
        fprintf(stderr,"The new size cant be zero!");
        exit(EXIT_FAILURE);
    }
}
void write_memory_sequentially_extend(wav_header_t header,int32_t *data, uint32_t num_samples, uint32_t silence_len, 
FILE *input_file, FILE *output_file, long metadata_bytes){
    size_t size = (header.bits_per_sample / 8);
     if(size == 3 && header.num_channels == 2){
        num_samples-=header.sample_rate*2;
    }
    if(num_samples * size > MAX_RAM_USAGE){
        int split = 1;
        while (num_samples * size > MAX_RAM_USAGE)
        {
            split *= 2;
            num_samples /= 2;
        }
        for (size_t i = 0; i < split; i++)
        {
            double percent = ((double)i * 100 / (split));
            printf("Progres:%c%.3g\n",'%',percent);
            data = malloc(num_samples * size);
            check_if_there_is_not_enough_memory_and_exit_if_there_isnt(data);
            fread(data, size, num_samples, input_file); //copy existing data
            fwrite(data, size, num_samples, output_file);
            free(data);
        }
        
    } else{
        data = malloc(num_samples * (size));
        check_if_there_is_not_enough_memory_and_exit_if_there_isnt(data);
        fread(data, size, num_samples, input_file); //copy existing data
        fwrite(data, size, num_samples, output_file);
        free(data);
    }
    if(silence_len * size > MAX_RAM_USAGE){
        int split = 1;
        while (silence_len * size > MAX_RAM_USAGE)
        {
            
            split *= 2;
            silence_len /= 2;
        }
        for (size_t i = 0; i < split; i++)
        {
            double percent = ((double)i * 100 / (split));
            printf("Progress:%c%.3g\n",'%',percent);
            data = malloc(silence_len * size); // reallocate space for the silence samples
            check_if_there_is_not_enough_memory_and_exit_if_there_isnt(data);
            memset(data, 0, silence_len * size); //set the samples to 0
            fwrite(data, size,silence_len, output_file);
            free(data);
        }
    } else {
    data = malloc(silence_len * size); // reallocate space for the silence samples
    check_if_there_is_not_enough_memory_and_exit_if_there_isnt(data);
    memset(data, 0, silence_len * size); //set the samples to 0
    fwrite(data, size,silence_len, output_file);
    free(data);
    }
    append_additional_metadata_to_resized_file(input_file, output_file, metadata_bytes);
}
void write_memory_sequentially_trim(wav_header_t header,int32_t *data, uint32_t num_samples, 
FILE *input_file, FILE *output_file, long metadata_bytes){
    size_t size = (header.bits_per_sample / 8);
    if(num_samples * size > MAX_RAM_USAGE){
        int split = 1;
        while (num_samples * size > MAX_RAM_USAGE)
        {
            split *= 2;
            num_samples /= 2;
        }
        for (size_t i = 0; i < split; i++)
        {
            double percent = ((double)i * 100 / (split));
            printf("Progress:%c%.3g\n",'%',percent);
            data = malloc(num_samples * size);
            check_if_there_is_not_enough_memory_and_exit_if_there_isnt(data);
            fread(data, size, num_samples, input_file); //copy existing data
            fwrite(data, size, num_samples, output_file);
            free(data);
        }
        
    } else{
        data = malloc(num_samples * size);
        check_if_there_is_not_enough_memory_and_exit_if_there_isnt(data);
        fread(data, size, num_samples, input_file); //copy existing data
        fwrite(data, size, num_samples, output_file);
        free(data);
    }
    append_additional_metadata_to_resized_file(input_file, output_file, metadata_bytes);
}
void read_and_fill_in_additional_metadata_if_found(wav_header_t header, wav_additional_data_t *additional_data, FILE *input_file){
    char buff[2];
    int id_flag = 0;
    while (!id_flag)
    {
        fread(buff, sizeof(buff), 1, input_file);
        if(!strncmp("id", buff,2)){
            fread(buff, sizeof(buff), 1, input_file);
            if(!strncmp("3 ", buff,2)) break;
            fseek(input_file, -2, SEEK_CUR); // don't miss out on previous data if false positive
        }
        if(!strncmp("IN", buff,2)){
            fread(buff, sizeof(buff), 1, input_file);
            if(!strncmp("AM", buff,2)){
                fill_in_property_from_additional_metadata(1, additional_data, input_file);
                continue;
            } 
            fseek(input_file, -2, SEEK_CUR); 
        }
        if(!strncmp("IP", buff,2)){
            fread(buff, sizeof(buff), 1, input_file);
            if(!strncmp("RD", buff,2)){
                fill_in_property_from_additional_metadata(2, additional_data, input_file);
                continue;
            } 
            fseek(input_file, -2, SEEK_CUR); 
        }
        if(!strncmp("IA", buff,2)){
            fread(buff, sizeof(buff), 1, input_file);
            if(!strncmp("RT", buff,2)){
                fill_in_property_from_additional_metadata(3, additional_data, input_file);
                continue;
            } 
            fseek(input_file, -2, SEEK_CUR); 
        }
        if(!strncmp("IC", buff,2)){
            fread(buff, sizeof(buff), 1, input_file);
            if(!strncmp("MT", buff,2)){
                fill_in_property_from_additional_metadata(4, additional_data, input_file);
                continue;
            }
            if(!strncmp("RD", buff,2)){
                fill_in_property_from_additional_metadata(5, additional_data, input_file);
                continue;
            } 
            fseek(input_file, -2, SEEK_CUR);
        }
        if(!strncmp("IG", buff,2)){
            fread(buff, sizeof(buff), 1, input_file);
            if(!strncmp("NR", buff,2)){
                fill_in_property_from_additional_metadata(6, additional_data, input_file);
                continue;
            } 
            fseek(input_file, -2, SEEK_CUR); 
        }
        if(!strncmp("IT", buff, 2)){
            fread(buff, sizeof(buff), 1, input_file);
            if(!strncmp("RK", buff, 2)){
                fill_in_property_from_additional_metadata(7, additional_data, input_file);
                continue;
            } 
            fseek(input_file, -2, SEEK_CUR);
        }
    }
}
int check_if_additional_information_is_found_and_set_position_if_it_is(wav_header_t header, wav_additional_data_t *additional_data, FILE *input_file){
    fseek(input_file, header.chunk_size-BYTES_TO_SEARCH_FOR_LIST_OFFSET, SEEK_SET);
    int li_flag = 0;
    char buff[2];
    long bytes_offset = 0;
    for (int i = 0; i < BYTES_TO_SEARCH_FOR_LIST_OFFSET; i+=2)
    {
        fread(buff, sizeof(buff), 1, input_file);
        if(strncmp(buff,"LI",2) == 0){
            bytes_offset = ftell(input_file);
            li_flag = 1;
            continue;
        }
        if(li_flag && strncmp(buff,"ST",2) == 0){
            printf("Additional information found!\n");
            fseek(input_file, -2, SEEK_CUR);
            return (int)(header.chunk_size - bytes_offset)+10; // i-2 because of LI offset
        }
        li_flag = 0;
    }
    printf("Additional information not found!\n");
    return 0;
}
void fill_in_property_from_additional_metadata(int code, wav_additional_data_t *additional_data, FILE *input_file){
        //Codes
    // 1.INAM - Track Title
    // 2.IPRD - Album name
    // 3.IART - Artist Name
    // 4.ICMT - Comment
    // 5.ICRD - Year
    // 6.IGNR - Genre
    // 7.ITRK - Track Count
    switch (code)
    {
    case 1:
        strncpy(additional_data->name_flag, "INAM",4);
        fread(&(additional_data->name_len), sizeof(uint32_t), 1, input_file);
        additional_data->track_title = malloc(additional_data->track_len);
        fread((additional_data->track_title), additional_data->name_len, 1, input_file);
        printf("Track title:%s\n", additional_data->track_title);
        break;
    case 2:
        strncpy(additional_data->album_flag, "IPRD",4);
        fread(&(additional_data->album_len), sizeof(uint32_t), 1, input_file);
        additional_data->album_name = malloc(additional_data->album_len);
        fread((additional_data->album_name), additional_data->album_len, 1, input_file);
        printf("Album name:%s\n", additional_data->album_name);
        break;
    case 3:
        strncpy(additional_data->artist_flag, "IART",4);
        fread(&(additional_data->artist_len), sizeof(uint32_t), 1, input_file);
        additional_data->artist_name = malloc(additional_data->artist_len);
        fread((additional_data->artist_name), additional_data->artist_len, 1, input_file);
        printf("Artist name:%s\n", additional_data->artist_name);
        break;
    case 4:
        strncpy(additional_data->comment_flag, "ICMT",4);
        fread(&(additional_data->comment_len), sizeof(uint32_t), 1, input_file);
        additional_data->comment = malloc(additional_data->comment_len);
        fread((additional_data->comment), additional_data->comment_len, 1, input_file);
        printf("Comment:%s\n", additional_data->comment);
        break;
    case 5:
        strncpy(additional_data->year_flag, "ICRD",4);
        fread(&(additional_data->year_len), sizeof(uint32_t), 1, input_file);
        additional_data->year = malloc(additional_data->year_len);
        fread((additional_data->year), additional_data->year_len, 1, input_file);
        printf("Year:%s\n", additional_data->year);
        break;
    case 6:
        strncpy(additional_data->genre_flag, "IGNR",4);
        fread(&(additional_data->genre_len), sizeof(uint32_t), 1, input_file);
        additional_data->genre = malloc(additional_data->genre_len);
        fread((additional_data->genre), additional_data->genre_len, 1, input_file);
        printf("Genre:%s\n", additional_data->genre);
        break;
    case 7:
        strncpy(additional_data->track_flag, "ITRK",4);
        fread(&(additional_data->track_len), sizeof(uint32_t), 1, input_file);
        additional_data->track_count_data = malloc(additional_data->track_len);
        fread((additional_data->track_count_data), additional_data->track_len, 1, input_file);
        printf("Track count:%s\n", additional_data->track_count_data);
        break;
    default:
    printf("Probably a typo!\n");
        break;
    }
}
void append_additional_metadata_to_resized_file(FILE *input_file, FILE *output_file, int bytes_to_append){
    fseek(input_file, -bytes_to_append, SEEK_END);
    char buffer[bytes_to_append];
    fread(buffer, sizeof(buffer), 1, input_file);
    fwrite(buffer, sizeof(buffer), 1, output_file);
}
void free_additional_metadata_resources(wav_additional_data_t *additional_data){
    if(!strncmp(additional_data->track_flag, "ITRK",4)){
         free(additional_data->track_count_data);
    }
    if(!strncmp(additional_data->name_flag, "INAM",4)){
          free(additional_data->track_title);
    }
    if(!strncmp(additional_data->album_flag, "IPRD",4)){
        free(additional_data->album_name);
    }
    if(!strncmp(additional_data->artist_flag, "IART",4)){
         free(additional_data->artist_name);
    }
    if(!strncmp(additional_data->comment_flag, "ICMT",4)){
         free(additional_data->comment);
    }
    if(!strncmp(additional_data->genre_flag, "IGNR",4)){
         free(additional_data->genre);
    }
    if(!strncmp(additional_data->year_flag, "ICRD",4)){
         free(additional_data->year);
    }
}