#include "main_io.h"
#include "wav_file_structure.h"
#include "wav_operations.h"
#include "log_header.h"
int main(int argc, char **argv){
    int overwrite_flag = 0,silent_flag = 0;
    FILE *input_file, *output_file;
    char input_filename[FILENAME_SIZE], *output_filename, new_wav_length[WAV_LENGTH_FORMAT_SIZE];
    wav_header_t header_metadata;
    start_of_the_program(&overwrite_flag, &silent_flag, argc, argv, input_filename, output_filename, input_file,
    output_file, header_metadata, new_wav_length);
    return EXIT_SUCCESS;
}