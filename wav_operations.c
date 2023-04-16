#include "wav_operations.h"
FILE *open_wav_file_and_return_error_if_encountered(char *filename, int silent_flag){
    log_function(silent_flag, open_wav_file_and_return_error_if_encountered);
    FILE *file_pointer = fopen(filename, "rb");
    if (file_pointer == NULL) {
        fprintf(stderr, "Error opening input file\n");
        exit(1);
    }
    log_function_parameter(silent_flag, filename,filename,s);
    log_function_return(silent_flag, open_wav_file_and_return_error_if_encountered, file_pointer, p);
    return file_pointer;
}
void print_out_wav_file_metadata_easy_way(wav_header_t wav_struct, int silent_flag){
    log_function(silent_flag, print_out_wav_file_metadata_easy_way);
    printf("Chunk ID: %.4s\n", wav_struct.chunk_id);
    printf("Chunk Size: %u\n", wav_struct.chunk_size);
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
    printf("Subchunk2 Size: %hu\n", wav_struct.subchunk2_size);
}
void print_out_wav_file_length_in_specified_format(wav_header_t wav_struct, int silent_flag){
    log_function(silent_flag, print_out_wav_file_length_in_specified_format);
    uint32_t length = return_length_of_file_in_seconds(wav_struct,silent_flag);
    int hours = (int) length/3600;
    int easier_format = (int) length % 3600;
    int minutes = easier_format/60;
    int seconds = easier_format % 60;
    printf("The length of the file content is %.02d:%.02d:%.02d\n", hours,minutes,seconds);
}
void check_if_the_wav_file_has_correct_metadata_structure(wav_header_t header, int silent_flag){
    log_function(silent_flag, check_if_the_wav_file_has_correct_metadata_structure);
    if (strncmp(header.chunk_id, "RIFF", 4) != 0 ||
        strncmp(header.format, "WAVE", 4) != 0 ||
        strncmp(header.subchunk1_ID, "fmt ", 4) != 0 ||
        strncmp(header.subchunk2_ID, "data", 4) != 0) {
        fprintf(stderr, "Input file is not a WAV correct file\n");
        exit(EXIT_FAILURE);
    }
}
void extend_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, char *input_filename, char *output_filename, int silent_flag){
    log_function(silent_flag, extend_the_wav_file_with_specified_duration_in_seconds);
    uint32_t num_samples = header.subchunk2_size / sizeof(int16_t); //get sampples
    int16_t *data;
    data = malloc(num_samples * sizeof(int16_t));
    fread(data, sizeof(int16_t), num_samples, input_file); //copy existing data
    uint32_t silence_len = (uint32_t)(duration * header.sample_rate); // number of silence samples
    data = realloc(data, (num_samples + silence_len) * sizeof(int16_t)); // reallocate space for the silence samples
    memset(&data[num_samples], 0, silence_len * sizeof(int16_t)); //set the samples to 0
    //update the wav header
    header.chunk_size = 36 + (num_samples + silence_len) * sizeof(int16_t);
    header.subchunk2_size = (num_samples + silence_len) * sizeof(int16_t);
    // write to wav
    fwrite(&header, sizeof(wav_header_t), 1, output_file);
    fwrite(data, sizeof(int16_t), num_samples + silence_len, output_file);
    log_function_parameter(silent_flag, input_file, input_file, p);
    log_function_parameter(silent_flag, output_file, output_file, p);
    log_function_parameter(silent_flag, duration, duration, g);
    log_function_parameter(silent_flag, input_filename, input_filename, s);
    log_function_parameter(silent_flag, output_filename, output_filename, s);
    free_resources(input_file, output_file, data,silent_flag);
}
void trim_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, char *input_filename, char *output_filename, int silent_flag){
    log_function(silent_flag, trim_the_wav_file_with_specified_duration_in_seconds);
    int16_t *data;
    uint32_t num_samples, sample_duration_to_be_removed;
    num_samples = header.subchunk2_size / sizeof(int16_t);
    sample_duration_to_be_removed = (uint32_t)(duration * header.sample_rate);
    num_samples -= sample_duration_to_be_removed;
    data = malloc((num_samples) * sizeof(int16_t));
    fread(data, sizeof(int16_t), (num_samples), input_file);
    int length = header.subchunk2_size / (header.sample_rate * header.num_channels * header.bits_per_sample / 8);
    header.chunk_size = 36 + num_samples * sizeof(int16_t);
    header.subchunk2_size = num_samples * sizeof(int16_t);
    fwrite(&header, sizeof(wav_header_t), 1, output_file);
    fwrite(data, sizeof(int16_t), num_samples, output_file);
    log_function_parameter(silent_flag, input_file, input_file, p);
    log_function_parameter(silent_flag, output_file, output_file, p);
    log_function_parameter(silent_flag, duration, duration, g);
    log_function_parameter(silent_flag, input_filename, input_filename, s);
    log_function_parameter(silent_flag, output_filename, output_filename, s);
    free_resources(input_file, output_file, data, silent_flag);

}
uint32_t return_length_of_file_in_seconds(wav_header_t wav_struct, int silent_flag){
    log_function(silent_flag, return_length_of_file_in_seconds);
    log_function_return(silent_flag, return_length_of_file_in_seconds, wav_struct.subchunk2_size / (wav_struct.sample_rate * wav_struct.num_channels * wav_struct.bits_per_sample / 8), u);
    return wav_struct.subchunk2_size / (wav_struct.sample_rate * wav_struct.num_channels * wav_struct.bits_per_sample / 8);
}
void free_resources(FILE *input_file, FILE *output_file, int16_t *data, int silent_flag){
    log_function(silent_flag, free_resources);
    log_function_parameter(silent_flag, input_file, input_file, p);
    log_function_parameter(silent_flag, input_file, output_file, p);
    log_function_parameter(silent_flag, data, data, p);
    fclose(input_file);
    fclose(output_file);
    free(data);
}
void determine_whether_to_trim_extend_or_quit(uint32_t old_size, uint32_t new_size, wav_header_t header, FILE *input_file, 
                                            FILE *output_file, char *input_filename, char *output_filename, int silent_flag){
    log_function(silent_flag, determine_whether_to_trim_extend_or_quit);
    int diff = new_size - old_size;
    if(diff < 0){
        trim_the_wav_file_with_specified_duration_in_seconds(header, input_file, output_file, abs(diff), 
        input_filename, output_filename,silent_flag);
        printf("File successfully trimmed with %d seconds!\n", abs(diff));
    } else if(diff > 0){
        extend_the_wav_file_with_specified_duration_in_seconds(header, input_file, output_file, diff, 
        input_filename, output_filename,silent_flag);
        printf("File successfully extended with %d seconds!\n", diff);
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