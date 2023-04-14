#ifndef __MAIN_IO_H__
#define __MAIN_IO_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void safe_string_input(char *str, int length);
void prompt_for_filename_and_fill_in__filename(char *filename);
void check_for_additional_arguments(int *o_flag, int *s_flag, int argc, char **argv);
void check_if_the_filename_is_invalid(char *filename);
#endif