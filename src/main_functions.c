#include "main_functions.h"
void check_for_additional_arguments(int *o_flag, int *s_flag, int argc, char **argv){
    if(argc < 2){
        printf("No additional arguments\n");
        return;
    }
    for (int i = 1; i < argc; i++)
    {
        if((strcmp("-s", argv[i]) == 0)){
            printf("Silent mode!\n");
            *s_flag = 1;
        }
        if((strcmp("-o", argv[i]) == 0)){
            printf("Overwrite mode!\n");
            *o_flag = 1;
        }
    }
    
}
void prompt_for_filename_and_fill_in_filename(char *filename, int silent_flag){
    log_function(silent_flag, prompt_for_filename_and_fill_in_filename);
    printf("Please enter the name of the wav file you want to resize!\n");
    safe_string_input(filename, FILENAME_SIZE);
    log_function_parameter(silent_flag, filename, filename, s);
}
void safe_string_input(char *str, int length){
    fgets(str, length, stdin);
    if(str[strlen(str)-1] != '\n'){
        while ((getc(stdin) != '\n'));
    }
    str[strlen(str)-1] = '\0';
}
void check_if_the_filename_is_invalid_and_exit_if_it_is(char *filename, int silent_flag){
    log_function(silent_flag, check_if_the_filename_is_invalid_and_exit_if_it_is);
    if(strlen(filename) < 4){
        printf("Invalid file type!\n");
        exit(EXIT_FAILURE);
    }
    log_function_parameter(silent_flag, filename, filename, s);
    char acceptable[4] = ".wav";
    char *ptr_to_acc = acceptable;
    for (int i = strlen(filename)-4; i < strlen(filename); i++)
    {
        if(filename[i] != *(ptr_to_acc++)){
            printf("Invalid file type!\n");
            exit(EXIT_FAILURE);
        }
    }
    log_function_parameter(silent_flag, filename, filename, s);
    
}
char *return_new_output_filename(char *input_filename, int silent_flag){
    log_function(silent_flag, return_new_output_filename);
    char *filename = malloc((strlen(input_filename)+strlen("-modified"))+1);
    check_if_there_is_not_enough_memory_and_exit_if_there_isnt(filename);
    char ending[] = "-modified.wav";
    int j = 0;
    for (size_t i = 0; i < strlen(input_filename) - 4; i++)
    {
        *(filename+i) = *(input_filename+i);
        j++;
    }
    for (size_t i = 0; i < 14; i++)
    {
        *(filename+i+j) = *(ending+i);
    }
    log_function_parameter(silent_flag, input_filename, input_filename, s);
    log_function_return(silent_flag, return_new_output_filename, filename, s);
    return filename;
}
FILE  *open_the_output_file_and_exit_if_error_encountered(char *output_filename, int silent_flag){
    log_function(silent_flag, open_the_output_file_and_exit_if_error_encountered);
    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        printf("%s", output_filename);
        fprintf(stderr, "Error opening output file\n");
        exit(EXIT_FAILURE);
    }
    log_function_parameter(silent_flag, output_filename, output_filename, s);
    log_function_return(silent_flag, open_the_output_file_and_exit_if_error_encountered, output_file, p);
    return output_file;
}
uint32_t return_length_in_seconds_from_string_format(char *input, int silent_flag){
    log_function(silent_flag, return_length_in_seconds_from_string_format);
    if(strlen(input) != 8){
        fprintf(stderr, "Wrong input format");
        exit(EXIT_FAILURE);
    }
    char hours[3], minutes[3], seconds[3];
    hours[0] = input[0];
    hours[1] = input[1];
    hours[2] = '\0';
    minutes[0] = input[3];
    minutes[1] = input[4];
    minutes[2] = '\0';
    seconds[0] = input[6];
    seconds[1] = input[7];
    seconds[2] = '\0';
    uint32_t seconds_d = atoi(seconds);
    seconds_d += 60 * atoi(minutes);
    seconds_d += 3600 * atoi(hours);
    log_function_parameter(silent_flag, input, input, s);
    log_function_return(silent_flag, return_length_in_seconds_from_string_format, seconds_d, u);
    return seconds_d;
}
void prompt_for_new_length_in_specified_format(char *new_length, int silent_flag){
    log_function(silent_flag, prompt_for_new_length_in_specified_format);
    printf("Please enter the new length in the specified format (<hh>:<mm>:<ss>)!\n");
    safe_string_input(new_length, WAV_LENGTH_FORMAT_SIZE);
    log_function_parameter(silent_flag, new_length, new_length, s);
}
void remove_old_file_if_overwrite_flag_is_present(int overwrite_flag, char *input_filename, int silent_flag){
    log_function(silent_flag, remove_old_file_if_overwrite_flag_is_present);
    log_function_parameter(silent_flag, input_filename, input_filename, s);
    log_function_parameter(silent_flag, overwrite_flag, overwrite_flag, d);
    if(overwrite_flag){
        remove(input_filename);
    }
}
void start_of_the_program(int *overwrite_flag, int *silent_flag, int argc, char **argv, char *input_filename, char *output_filename,
    FILE *input_file,FILE *output_file, wav_header_t header_metadata, char *new_wav_length){
    check_for_additional_arguments(overwrite_flag, silent_flag, argc, argv);
    log_function(*silent_flag, start_of_the_program);
    prompt_for_filename_and_fill_in_filename(input_filename, *silent_flag);
    check_if_the_filename_is_invalid_and_exit_if_it_is(input_filename, *silent_flag);
    output_filename = return_new_output_filename(input_filename, *silent_flag);
    input_file = open_wav_file_and_exit_if_error_encountered(input_filename,*silent_flag);
    read_the_metadata_for_the_wav_file(&header_metadata, input_file);
    check_if_the_wav_file_has_correct_metadata_structure_and_exit_if_not(header_metadata,*silent_flag);
    print_out_wav_file_metadata(header_metadata,*silent_flag);
    print_out_wav_file_length_in_specified_format(header_metadata,*silent_flag);
    prompt_for_new_length_in_specified_format(new_wav_length,*silent_flag);
    output_file = open_the_output_file_and_exit_if_error_encountered(output_filename,*silent_flag);
    uint32_t old_size = return_length_of_wav_file_in_seconds(header_metadata,*silent_flag);
    uint32_t new_size = return_length_in_seconds_from_string_format(new_wav_length,*silent_flag);
    check_if_new_size_is_zero_and_exit_if_true(new_size);
    determine_whether_to_trim_extend_or_quit(old_size, new_size, header_metadata, input_file, output_file,
    input_filename, output_filename,*silent_flag);
    remove_old_file_if_overwrite_flag_is_present(*overwrite_flag, input_filename,*silent_flag);
    free(output_filename);
}
