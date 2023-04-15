#ifndef __WAV_OPERATIONS__
#define __WAV_OPERATIONS__
#include "wav_file_structure.h"
#include <stdio.h>
#include <stdlib.h>
void print_out_wav_file_metadata_easy_way(wav_header_t wav_struct);
void print_out_wav_file_metadata_harder_way(wav_header_t *wav_struct, FILE *file_pointer);
#endif