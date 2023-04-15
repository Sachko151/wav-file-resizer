#include "main_io.h"
#include "wav_file_structure.h"
#include <inttypes.h>
#include "wav_operations.h"
FILE *open_wav_file_and_return_error_if_encountered(char *filename);

uint32_t convert_from_little_to_big_endian_uint32(unsigned char buffer[4]);
int main(int argc, char **argv){
    int overwrite_flag = 0;
    int silent_flag = 0;
    FILE *ptr;
    char filename[32];
    wav_header_t header_metadata;
    check_for_additional_arguments(&overwrite_flag, &silent_flag, argc, argv);
    prompt_for_filename_and_fill_in__filename(filename);
    check_if_the_filename_is_invalid(filename);
    ptr = open_wav_file_and_return_error_if_encountered(filename);
    fread(&header_metadata, sizeof(wav_header_t), 1, ptr);
    print_out_wav_file_metadata_easy_way(header_metadata);
    return 0;
}