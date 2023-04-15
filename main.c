#include "main_io.h"
#include "wav_file_structure.h"
#include <inttypes.h>
#include "wav_operations.h"
#define FILENAME "wav_samples/2.wav"

void check_if_the_wav_file_has_correct_metadata_structure(wav_header_t header);
void calculate_the_new_data_and_write_to_output_file(wav_header_t header, FILE *input_file, double duration, char *input_filename);
char *return_new_output_filename(char *input_filename);
int main(int argc, char **argv){
    int overwrite_flag = 0;
    int silent_flag = 0;
    FILE *ptr;
    char filename[32];
    wav_header_t header_metadata;
    check_for_additional_arguments(&overwrite_flag, &silent_flag, argc, argv);
    // prompt_for_filename_and_fill_in__filename(filename);
    // check_if_the_filename_is_invalid(filename);
    ptr = open_wav_file_and_return_error_if_encountered(FILENAME);
    fread(&header_metadata, sizeof(wav_header_t), 1, ptr);
    // check_if_the_wav_file_has_correct_metadata_structure(header_metadata);
    // print_out_wav_file_metadata_easy_way(header_metadata);
    calculate_the_new_data_and_write_to_output_file(header_metadata, ptr, 5, FILENAME);
    return EXIT_SUCCESS;
}
void check_if_the_wav_file_has_correct_metadata_structure(wav_header_t header){
    if (strncmp(header.chunk_id, "RIFF", 4) != 0 ||
        strncmp(header.format, "WAVE", 4) != 0 ||
        strncmp(header.subchunk1_ID, "fmt ", 4) != 0 ||
        strncmp(header.subchunk2_ID, "data", 4) != 0) {
        fprintf(stderr, "Input file is not a WAV correct file\n");
        exit(EXIT_FAILURE);
    }
}
void calculate_the_new_data_and_write_to_output_file(wav_header_t header, FILE *input_file, double duration, char *input_filename){
    // Get the number of samples and allocate memory for the audio data
    uint32_t numSamples = header.subchunk2Size / sizeof(int16_t);
    int16_t *data;
    data = malloc(numSamples * sizeof(int16_t));
    fread(data, sizeof(int16_t), numSamples, input_file);

    // Determine the number of samples of silence to add
    uint32_t silenceLen = (uint32_t)(duration * header.sample_rate);

    // Append the digital silence samples to the end of the audio data
    data = realloc(data, (numSamples + silenceLen) * sizeof(int16_t));
    memset(&data[numSamples], 0, silenceLen * sizeof(int16_t));

    // Update the WAV header with the new file size
    header.chunk_size = 36 + numSamples * sizeof(int16_t) + silenceLen * sizeof(int16_t);
    header.subchunk2Size = numSamples * sizeof(int16_t) + silenceLen * sizeof(int16_t);
    char *output_filename = return_new_output_filename(input_filename);
    FILE *outfile = fopen(output_filename, "wb");
    if (!outfile) {
        fprintf(stderr, "Failed to open output file\n");
        free(data);
        fclose(input_file);
        exit(EXIT_FAILURE);
    }

    // Write the WAV header and audio data to the output file
    fwrite(&header, sizeof(wav_header_t), 1, outfile);
    fwrite(data, sizeof(int16_t), numSamples + silenceLen, outfile);

    // Close the input and output files
    fclose(input_file);
    fclose(outfile);

    // Free the memory allocated for the audio data
    free(data);
}
char *return_new_output_filename(char *input_filename){
    char *filename = malloc((strlen(input_filename)+strlen("-modified"))+1);
    for (size_t i = 0; i < strlen(input_filename) - 4; i++)
    {
        *(filename+i) = *(input_filename+i);
    }
    strncat(filename, "-modified.wav", 14);
    return filename;
}