#ifndef __WAV_OPERATIONS__
#define __WAV_OPERATIONS__
#include "wav_file_structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_functions.h"
#include "log.h"
#define MAX_RAM_USAGE 134217728
#define BYTES_TO_SEARCH_FOR_LIST_OFFSET 512
FILE *open_wav_file_and_exit_if_error_encountered(char *filename, int silent_flag);
//--------------------
//DESCRIPTION: open_wav_file_and_exit_if_error_encountered
//This function opens the input file specified from the filename string and exits if an error is encountered
//PARAMETERS:
//char *filename pointer to the filename and silent_flag for additional logging
//RETURN VALUE:
//file pointer pointing to the input_filename
//----------------------- 
void print_out_wav_file_metadata(wav_header_t wav_struct, int silent_flag);
//--------------------
//DESCRIPTION: print_out_wav_file_metadata
//This function prints to stdout all the info from the wav_header_t struct
//PARAMETERS:
//wav_header_t wav_struct - struct where the information is, int silent_flag - for additional logging
//RETURN VALUE:
//void
//----------------------- 
void check_if_the_wav_file_has_correct_metadata_structure_and_exit_if_not(wav_header_t header, int silent_flag);
//--------------------
//DESCRIPTION: check_if_the_wav_file_has_correct_metadata_structure_and_exit_if_not
//This function checks the integrity of the wav file and exits if an error is encountered
//PARAMETERS:
//wav_header_t wav_struct - struct where the information is, int silent_flag - for additional logging
//RETURN VALUE:
//void
//----------------------- 
void extend_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, char *input_filename, 
char *output_filename, int silent_flag, long metadata_bytes);
//--------------------
//DESCRIPTION: extend_the_wav_file_with_specified_duration_in_seconds
//This function prepares the wav file by writing to the header with the updated values
//PARAMETERS:
//wav_header_t wav_struct - struct where the information is, int silent_flag - for additional logging
// FILE *input_file - pointer to input file, FILE *output_file pointer to output file, 
//double duration - time to extend by, char *input_filename - string of input_filename, 
//char *output_filename - string of output_filename, long metadata_bytes - the offset with which the ILIST metadata to be appended
//RETURN VALUE:
//void
//----------------------- 
void free_resources(FILE *input_file, FILE *output_file,  int silent_flag);
//--------------------
//DESCRIPTION: free_resources
//This function frees the input_file, output_file from their usage.
//PARAMETERS:
//FILE *input_file - pointer to input file, FILE *output_file pointer to output file, int silent_flag - for additional logging
//RETURN VALUE:
//void
//----------------------- 
void print_out_wav_file_length_in_specified_format(wav_header_t wav_struct, int silent_flag);
//--------------------
//DESCRIPTION: print_out_wav_file_length_in_specified_format
//This function prints the length of the wav file based from the information from its header.
//PARAMETERS:
//wav_header_t wav_struct - struct where the information is, int silent_flag - for additional logging
//RETURN VALUE:
//void
//----------------------- 
void trim_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, 
char *input_filename, char *output_filename, int silent_flag, long metadata_bytes);
//--------------------
//DESCRIPTION: trim_the_wav_file_with_specified_duration_in_seconds
//This function prepares the wav file by writing to the header with the updated values
//PARAMETERS:
//wav_header_t wav_struct - struct where the information is, int silent_flag - for additional logging
// FILE *input_file - pointer to input file, FILE *output_file pointer to output file, 
//double duration - time to extend by, char *input_filename - string of input_filename, 
//char *output_filename - string of output_filename, long metadata_bytes - the offset with which the LIST metadata to be appended
//RETURN VALUE:
//void
//----------------------- 
uint32_t return_length_of_wav_file_in_seconds(wav_header_t wav_struct, int silent_flag);
//--------------------
//DESCRIPTION: return_length_of_wav_file_in_seconds
//This function returns the length of the wav file based on the content form the wav_header_t struct
//PARAMETERS:
//wav_header_t wav_struct - struct where the information is, int silent_flag - for additional logging
//RETURN VALUE:
//unsigned 32-bit integer
//-----------------------
void read_the_metadata_for_the_wav_file(wav_header_t *header_metadata, FILE *input_file);
//--------------------
//DESCRIPTION: read_the_metadata_for_the_wav_file
//This function loads the header data from the input_file to the struct
//PARAMETERS:
//wav_header_t *header_metadata - pointer to the struct, FILE *input_file - the wav file
//RETURN VALUE:
//void
//-----------------------
void determine_whether_to_trim_extend_or_quit(uint32_t old_size, uint32_t new_size, wav_header_t header, FILE *input_file, 
                                FILE *output_file, char *input_filename, char *output_filename, int silent_flag, long metadata_bytes);
//--------------------
//DESCRIPTION: determine_whether_to_trim_extend_or_quit
//This function determines the action by looking at the difference between new size and old size
//PARAMETERS:
//uint32_t old_size - old_size of wav file in seconds, uint32_t new_size - new_size of wav file in seconds, 
//wav_header_t header - header struct with data in it about the wav file, FILE *input_file - pointer to the input file, 
//FILE *output_file - pointer to the output file, char *input_filename, char *output_filename, int silent_flag, long metadata_bytes - the offset with which the LIST metadata to be appended
//RETURN VALUE:
//void
//-----------------------
void change_duration_so_that_it_works_with_stereo(wav_header_t header, uint32_t *new_size, uint32_t *old_size, int *diff, int *display_diff);
//--------------------
//DESCRIPTION: change_duration_so_that_it_works_with_stereo
//This function changed the difference in seconds for extending or trimming
//PARAMETERS:
//wav_header_t header_metadata - struct with info in it, uint32_t old_size - old_size of wav file in seconds, uint32_t new_size - new_size of wav file in seconds, 
//int *diff - pointer with actual difference to work with, int *display_diff - pointer with cosmetic difference to print out
//RETURN VALUE:
//void
//-----------------------
void check_if_there_is_not_enough_memory_and_exit_if_there_isnt(void *ptr);
//--------------------
//DESCRIPTION: check_if_there_is_not_enough_memory_and_exit_if_there_isnt
//This function checks if memory is allocated. and exits if there isnt
//PARAMETERS:
//void *ptr - pointer to memory
//RETURN VALUE:
//void
//-----------------------
void write_memory_sequentially_extend(wav_header_t header,int32_t *data, uint32_t num_samples, uint32_t silence_len, 
FILE *input_file, FILE *output_file, long metadata_bytes);
//--------------------
//DESCRIPTION: write_memory_sequentially_extend
//This function extends the wav file by buffers of predefined ram so that it can work with larger files without crashing
//PARAMETERS:
//wav_header_t header_metadata - struct with info in it, int32_t *data - pointer with sample data, uint32_t num_samples - total num of samples 
//uint32_t silence_len - silence length is seconds, FILE *output_file - pointer to output file, FILE *input_file - pointer to input file
//long metadata_bytes - the offset with which the LIST metadata to be appended
//RETURN VALUE:
//void
//-----------------------
void write_memory_sequentially_trim(wav_header_t header,int32_t *data, uint32_t num_samples, 
FILE *input_file, FILE *output_file, long metadata_bytes);
//--------------------
//DESCRIPTION: write_memory_sequentially_trim
//This function trims the wav file by reading buffers of predefined ram so that it can work with larger files without crashing
//PARAMETERS:
//wav_header_t header_metadata - struct with info in it, int32_t *data - pointer with sample data, uint32_t num_samples - total num of samples 
//uint32_t silence_len - silence length is seconds, FILE *output_file - pointer to output file, FILE *input_file - pointer to input file
//long metadata_bytes - the offset with which the LIST metadata to be appended
//RETURN VALUE:
//void
//-----------------------
void read_and_fill_in_additional_metadata_if_found(wav_header_t header, wav_additional_data_t *additional_data, FILE *input_file);
//--------------------
//DESCRIPTION: read_and_fill_in_additional_metadata_if_found
//This function checks for additional information regarding Artist/Album etc.
//PARAMETERS:
//wav_header_t header_metadata - struct with header metadata, wav_additional_data_t *additional_data - pointer to the struct with the artist... info
//FILE *input_file - pointer to the input file
//RETURN VALUE:
//void
//-----------------------
int check_if_additional_information_is_found_and_set_position_if_it_is(wav_header_t header, wav_additional_data_t *additional_data, FILE *input_file);
//--------------------
//DESCRIPTION: check_if_additional_information_is_found_and_set_position_if_it_is
//This function checks for additional information and returns the position where the LIST flag is in the wav file
//PARAMETERS:
//wav_header_t header_metadata - struct with header metadata, wav_additional_data_t *additional_data - pointer to the struct with the artist... info
//FILE *input_file - pointer to the input file
//RETURN VALUE:
// 0 - not found, != 0 - position of the LIST FLAG
//-----------------------
void fill_in_property_from_additional_metadata(int code, wav_additional_data_t *additional_data, FILE *input_file);
//--------------------
//DESCRIPTION: fill_in_property_from_additional_metadata
//This function reads the input_file and adds the found parameters with their status code into the wav_additional_data_t struct.
//PARAMETERS:
//int code - used for the different options 1 - Artist 2 - Album etc.
//wav_additional_data_t *additional_data - pointer to the struct with the artist... info
//FILE *input_file - pointer to the input file
//RETURN VALUE:
//void
//-----------------------
void append_additional_metadata_to_resized_file(FILE *input_file, FILE *output_file, int bytes_to_append);
//--------------------
//DESCRIPTION: append_additional_metadata_to_resized_file
//This function appends (bytes_to_append) amount of bytes to the output file thus keeping the artist,album .. etc metadata
//PARAMETERS:
//FILE *input_file - pointer to the input file, FILE *output_file - pointer to the output file
//int bytes_to_append -amount of bytes to append from input to output at the end
//RETURN VALUE:
//void
//-----------------------
void free_additional_metadata_resources(wav_additional_data_t *additional_data);
//--------------------
//DESCRIPTION: free_additional_metadata_resources
//This function frees the strings allocated from the reading
//PARAMETERS:
//wav_additional_data_t *additional_data - pointer to the list metadata struct
//RETURN VALUE:
//void
//----------------------- 
#endif