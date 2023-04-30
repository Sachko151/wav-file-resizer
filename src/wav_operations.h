#ifndef __WAV_OPERATIONS__
#define __WAV_OPERATIONS__
#include "wav_file_structure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main_functions.h"
#include "log.h"
#include "gui_functions.h"
#define MAX_RAM_USAGE 134217728 //128 Mib
FILE *open_wav_file_and_exit_if_error_encountered(char *filename, int silent_flag);
void print_out_wav_file_metadata(wav_header_t wav_struct, int silent_flag);
int check_if_the_wav_file_has_correct_metadata_structure_and_exit_if_not(wav_header_t header, int silent_flag);
void extend_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, char *input_filename, char *output_filename, int silent_flag);
void free_resources(FILE *input_file, FILE *output_file,  int silent_flag);
void print_out_wav_file_length_in_specified_format(wav_header_t wav_struct, int silent_flag);
void trim_the_wav_file_with_specified_duration_in_seconds(wav_header_t header, FILE *input_file, FILE *output_file, double duration, char *input_filename, char *output_filename, int silent_flag);
uint32_t return_length_of_wav_file_in_seconds(wav_header_t wav_struct, int silent_flag);
void read_the_metadata_for_the_wav_file(wav_header_t *header_metadata, FILE *input_file);
void determine_whether_to_trim_extend_or_quit(uint32_t old_size, uint32_t new_size, wav_header_t header, FILE *input_file, 
                                            FILE *output_file, char *input_filename, char *output_filename, int silent_flag, GtkWidget *lbl_info);
void change_duration_so_that_it_works_with_stereo(wav_header_t header, uint32_t *new_size, uint32_t *old_size, int *diff, int *display_diff);
void check_if_there_is_not_enough_memory_and_exit_if_there_isnt(void *ptr);
void write_memory_sequentially_extend(int16_t *data, uint32_t num_samples, uint32_t silence_len, FILE *input_file, FILE *output_file);
void write_memory_sequentially_trim(int16_t *data, uint32_t num_samples, FILE *input_file, FILE *output_file);
#endif