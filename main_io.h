#ifndef __MAIN_IO_H__
#define __MAIN_IO_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define WAV_LENGTH_FORMAT_SIZE 16
void safe_string_input(char *str, int length);
void prompt_for_filename_and_fill_in_filename(char *filename);
void check_for_additional_arguments(int *o_flag, int *s_flag, int argc, char **argv);
void check_if_the_filename_is_invalid(char *filename);
char *return_new_output_filename(char *input_filename);
FILE  *open_the_output_file(char *output_filename);
uint32_t return_length_in_seconds_from_string_format(char *input);
void prompt_for_new_length_in_specified_format(char *new_length);
void remove_old_file_if_overwrite_flag_is_present(int overwrite_flag, char *input_filename);
#endif