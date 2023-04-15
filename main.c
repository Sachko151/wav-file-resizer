#include "main_io.h"
#include "wav_file_structure.h"
#include <inttypes.h>
#include "wav_operations.h"
#define FILENAME "wav_samples/2.wav"



int main(int argc, char **argv){
    int overwrite_flag = 0,silent_flag = 0;
    FILE *input_file, *output_file;
    char *input_filename, *output_filename;
    wav_header_t header_metadata;
    check_for_additional_arguments(&overwrite_flag, &silent_flag, argc, argv);
    // prompt_for_filename_and_fill_in__filename(filename);
    output_filename = return_new_output_filename(FILENAME);
    // check_if_the_filename_is_invalid(filename);
    input_file = open_wav_file_and_return_error_if_encountered(FILENAME);
    fread(&header_metadata, sizeof(wav_header_t), 1, input_file);
    // check_if_the_wav_file_has_correct_metadata_structure(header_metadata);
    // print_out_wav_file_metadata_easy_way(header_metadata);
    output_file = open_the_output_file(output_filename);
    calculate_the_new_data_and_write_to_output_file(header_metadata, input_file, output_file, 3, FILENAME, output_filename);
    return EXIT_SUCCESS;
}

