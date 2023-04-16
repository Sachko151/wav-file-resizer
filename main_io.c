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
void prompt_for_filename_and_fill_in_filename(char *filename){
    printf("Please enter the name of the wav file you want to resize!\n");
    safe_string_input(filename, 32);
}
void safe_string_input(char *str, int length){
    fgets(str, length, stdin);
    if(str[strlen(str)-1] != '\n'){
        while ((getc(stdin) != '\n'));
    }
    str[strlen(str)-1] = '\0';
}
void check_if_the_filename_is_invalid(char *filename){
    if(strlen(filename) < 4){
        printf("Invalid file type!\n");
        exit(1);
    }
    char acceptable[4] = ".wav";
    char *ptr_to_acc = acceptable;
    for (int i = strlen(filename)-4; i < strlen(filename); i++)
    {
        if(filename[i] != *(ptr_to_acc++)){
            printf("Invalid file type!\n");
            exit(1);
        }
    }
    
}
char *return_new_output_filename(char *input_filename){
    char *filename = malloc((strlen(input_filename)+strlen("-modified"))+1);
    for (size_t i = 0; i < strlen(input_filename) - 4; i++)
    {
        *(filename+i) = *(input_filename+i);
    }
    strncat(filename, "-modified.wav", 14);
    return filename;
}
FILE  *open_the_output_file(char *output_filename){
    FILE *output_file = fopen(output_filename, "wb");
    if (output_file == NULL) {
        printf("%s", output_filename);
        fprintf(stderr, "Error opening output file\n");
        exit(1);
    }
    return output_file;
}
uint32_t return_length_in_seconds_from_string_format(char *input){
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
    return seconds_d;
}
void prompt_for_new_length_in_specified_format(char *new_length){
    printf("Please enter the new length in the specified format (<hh>:<mm>:<ss>)!\n");
    safe_string_input(new_length, WAV_LENGTH_FORMAT_SIZE);
}
void remove_old_file_if_overwrite_flag_is_present(int overwrite_flag, char *input_filename){
    if(overwrite_flag){
        remove(input_filename);
    }
}