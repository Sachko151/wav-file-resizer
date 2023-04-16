#ifndef __WAV_OPERATIONS__
#define __WAV_OPERATIONS__
#include "wav_file_structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_io.h"
#include "log_header.h"
FILE *open_wav_file_and_return_error_if_encountered(char *filename, int silent_flag);
void print_out_wav_file_metadata_easy_way(wav_header_t wav_struct, int silent_flag);
void check_if_the_wav_file_has_correct_metadata_structure(wav_header_t header, int silent_flag);
void extend_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, char *input_filename, char *output_filename, int silent_flag);
void free_resources(FILE *input_file, FILE *output_file, int16_t *data, int silent_flag);
void print_out_wav_file_length_in_specified_format(wav_header_t wav_struct, int silent_flag);
void trim_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, char *input_filename, char *output_filename, int silent_flag);
uint32_t return_length_of_file_in_seconds(wav_header_t wav_struct, int silent_flag);
void determine_whether_to_trim_extend_or_quit(uint32_t old_size, uint32_t new_size, wav_header_t header, FILE *input_file, 
                                            FILE *output_file, char *input_filename, char *output_filename, int silent_flag);
#endif