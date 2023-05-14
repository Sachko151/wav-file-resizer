#ifndef __MAIN_IO_H__
#define __MAIN_IO_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "log.h"
#include "wav_file_structure.h"
#include "wav_operations.h"
#define WAV_LENGTH_FORMAT_SIZE 16
#define FILENAME_SIZE 256
void safe_string_input(char *str, int length);
//--------------------
//DESCRIPTION: safe_string_input
//I use this method to get strings and prevent buffer overflow
//PARAMETERS:
//pointer to the string and length
//RETURN VALUE:
//void
//-----------------------
void prompt_for_filename_and_fill_in_filename(char *filename, int silent_flag);
//--------------------
//DESCRIPTION: prompt_for_filename_and_fill_in_filename
//This method requests for the input wav file to be modified
//PARAMETERS:
//pointer to the string of filename and silent_flag for the additional logs
//RETURN VALUE:
//void
//-----------------------
void check_for_additional_arguments(int *o_flag, int *s_flag, int argc, char **argv);
//--------------------
//DESCRIPTION: check_for_additional_arguments
//This method checks for the additional flags during runtime
//PARAMETERS:
//pointer to the overwrite flag, pointer to the silent_flag 
//and the argument count and the pointer to the argument variables
//RETURN VALUE:
//void
//-----------------------
void check_if_the_filename_is_invalid_and_exit_if_it_is(char *filename, int silent_flag);
//--------------------
//DESCRIPTION: check_if_the_filename_is_invalid_and_exit_if_it_is
//This method checks if the file exists and exits if it doesnt (thus the name)
//PARAMETERS:
//pointer to the filename string and silent_flag for additional logging
//RETURN VALUE:
//void
//-----------------------
char *return_new_output_filename(char *input_filename, int silent_flag);
//--------------------
//DESCRIPTION: return_new_output_filename
//This method creates the output wav filename
//PARAMETERS:
//pointer to the input_filename string and silent_flag for additional logging
//RETURN VALUE:
//char pointer
//-----------------------
FILE  *open_the_output_file_and_exit_if_error_encountered(char *output_filename, int silent_flag);
//--------------------
//DESCRIPTION: open_the_output_file_and_exit_if_error_encountered
//This method opens the output file and returns the pointer to it, in case of an 
// error it terminates the program
//PARAMETERS:
//pointer to the input_filename string and silent_flag for additional logging
//RETURN VALUE:
//FILE pointer
//-----------------------
uint32_t return_length_in_seconds_from_string_format(char *input, int silent_flag);
//--------------------
//DESCRIPTION: return_length_in_seconds_from_string_format
//This method returns the seconds specified from the input format hh:mm:ss
// if an invalid input is provided it exits
//PARAMETERS:
//pointer to the input string and silent_flag for additional logging
//RETURN VALUE:
//unsigned 32-bit integer
//-----------------------
void prompt_for_new_length_in_specified_format(char *new_length, int silent_flag);
//--------------------
//DESCRIPTION: prompt_for_new_length_in_specified_format
//This method gets the new desired length of the wav file in the format hh:mm:ss
//PARAMETERS:
//pointer to the new_length string and silent_flag for additional logging
//RETURN VALUE:
//void
//-----------------------
void remove_old_file_if_overwrite_flag_is_present(int overwrite_flag, char *input_filename, int silent_flag);
//--------------------
//DESCRIPTION: remove_old_file_if_overwrite_flag_is_present
//This method removes the input file if the overwrite flag is present
//PARAMETERS:
//pointer to the input_filename string, silent_flag for additional logging and the overwrite_flag
//RETURN VALUE:
//void
//-----------------------
void start_of_the_program(int *overwrite_flag, int *silent_flag, int argc, char **argv, char *input_filename, char *output_filename,
    FILE *input_file,FILE *output_file, wav_header_t header_metadata, char *new_wav_length, wav_additional_data_t *additional_data);
//--------------------
//DESCRIPTION: start_of_the_program
//This method starts the program with the parameters specified in main.c
//PARAMETERS:
//int *overwrite_flag, int *silent_flag, int argc, char **argv, char *input_filename, char *output_filename,
// FILE *input_file,FILE *output_file, wav_header_t header_metadata, char *new_wav_length, wav_additional_data_t *additional_data
//RETURN VALUE:
//void
//----------------------- 
void check_if_new_size_is_zero_and_exit_if_true(uint32_t new_size);
//--------------------
//DESCRIPTION: check_if_new_size_is_zero_and_exit_if_true
//This method checks an edge case where the new size is 0 and exits if thats true
//PARAMETERS:
//new_size: size specified from the input
//RETURN VALUE:
//void
//-----------------------
#endif