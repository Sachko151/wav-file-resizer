#include "main_io.h"

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
    safe_string_input(filename, 32);
    log_function_parameter(silent_flag, filename, filename, s);
}
void safe_string_input(char *str, int length){
    fgets(str, length, stdin);
    if(str[strlen(str)-1] != '\n'){
        while ((getc(stdin) != '\n'));
    }
    str[strlen(str)-1] = '\0';
}
void check_if_the_filename_is_invalid(char *filename, int silent_flag){
    log_function(silent_flag, check_if_the_filename_is_invalid);
    if(strlen(filename) < 4){
        printf("Invalid file type!\n");
        exit(1);
    }
    log_function_parameter(silent_flag, filename, filename, s);
    char acceptable[4] = ".wav";
    char *ptr_to_acc = acceptable;
    for (int i = strlen(filename)-4; i < strlen(filename); i++)
    {
        if(filename[i] != *(ptr_to_acc++)){
            printf("Invalid file type!\n");
            exit(1);
        }
    }
    log_function_parameter(silent_flag, filename, filename, s);
    
}
char *return_new_output_filename(char *input_filename, int silent_flag){
    log_function(silent_flag, return_new_output_filename);
    char *filename = malloc((strlen(input_filename)+strlen("-modified"))+1);
    for (size_t i = 0; i < strlen(input_filename) - 4; i++)
    {
        *(filename+i) = *(input_filename+i);
    }
    strncat(filename, "-modified.wav", 14);
    log_function_parameter(silent_flag, input_filename, input_filename, s);
    log_function_return(silent_flag, return_new_output_filename, filename, s);
    return filename;
}
FILE  *open_the_output_file(char *output_filename, int silent_flag){
    log_function(silent_flag, open_the_output_file);
    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        printf("%s", output_filename);
        fprintf(stderr, "Error opening output file\n");
        exit(1);
    }
    log_function_parameter(silent_flag, output_filename, output_filename, s);
    log_function_return(silent_flag, open_the_output_file, output_file, p);
    return output_file;
}
uint32_t return_length_in_seconds_from_string_format(char *input, int silent_flag){
    log_function(silent_flag, return_length_in_seconds_from_string_format);
    if(strlen(input) != 8){
        fprintf(stderr, "Wrong input format");
        exit(1);
    }
    char hours[3], minutes[3], seconds[3];
    hours[0] = input[0];
    hours[1] = input[1];
    minutes[0] = input[3];
    minutes[1] = input[4];
    seconds[0] = input[6];
    seconds[1] = input[7];
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