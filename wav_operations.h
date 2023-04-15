#ifndef __WAV_OPERATIONS__
#define __WAV_OPERATIONS__
#include "wav_file_structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_io.h"
FILE *open_wav_file_and_return_error_if_encountered(char *filename);
void print_out_wav_file_metadata_easy_way(wav_header_t wav_struct);
void print_out_wav_file_metadata_harder_way(wav_header_t *wav_struct, FILE *file_pointer);
void check_if_the_wav_file_has_correct_metadata_structure(wav_header_t header);
void extend_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, char *input_filename, char *output_filename);
void free_resources(FILE *input_file, FILE *output_file, int16_t *data);
void print_out_wav_file_length_in_specified_format(wav_header_t wav_stuct);
void trim_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, char *input_filename, char *output_filename);
#endif