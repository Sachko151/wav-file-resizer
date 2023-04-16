#include "main_io.h"
#include "wav_file_structure.h"
#include <inttypes.h>
#include "wav_operations.h"
#define FILENAME "wav_samples/2.wav"
#define FILENAME_SIZE 256

int main(int argc, char **argv){
    int overwrite_flag = 0,silent_flag = 0;
    FILE *input_file, *output_file;
    char input_filename[FILENAME_SIZE], *output_filename, new_wav_length[WAV_LENGTH_FORMAT_SIZE];
    wav_header_t header_metadata;
    check_for_additional_arguments(&overwrite_flag, &silent_flag, argc, argv);
    prompt_for_filename_and_fill_in_filename(input_filename);
    check_if_the_filename_is_invalid(input_filename);
    output_filename = return_new_output_filename(input_filename);
    input_file = open_wav_file_and_return_error_if_encountered(input_filename);
    fread(&header_metadata, sizeof(wav_header_t), 1, input_file);
    check_if_the_wav_file_has_correct_metadata_structure(header_metadata);
    print_out_wav_file_metadata_easy_way(header_metadata);
    print_out_wav_file_length_in_specified_format(header_metadata);
    prompt_for_new_length_in_specified_format(new_wav_length);
    output_file = open_the_output_file(output_filename);
    uint32_t old_size = return_length_of_file_in_seconds(header_metadata);
    uint32_t new_size = return_length_in_seconds_from_string_format(new_wav_length);
    determine_whether_to_trim_extend_or_quit(old_size, new_size, header_metadata, input_file, output_file,
    input_filename, output_filename);
    return EXIT_SUCCESS;
}

