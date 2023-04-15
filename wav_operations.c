#include "wav_operations.h"
FILE *open_wav_file_and_return_error_if_encountered(char *filename){
    FILE *file_pointer = fopen(filename, "rb");
    if (file_pointer == NULL) {
        fprintf(stderr, "Error opening input file\n");
        exit(1);
    }
    return file_pointer;
}
void print_out_wav_file_metadata_easy_way(wav_header_t wav_struct){
    printf("Chunk ID: %.4s\n", wav_struct.chunk_id);
    printf("Chunk Size: %u\n", wav_struct.chunk_size);
    printf("Format: %.4s\n", wav_struct.format);
    printf("Subchunk1 ID: %.4s\n", wav_struct.subchunk1_ID);
    printf("Subchunk1 Size: %u\n", wav_struct.subchunk1_size);
    printf("Audio Format: %hu\n", wav_struct.audio_format);
    printf("Number of Channels: %hu\n", wav_struct.num_channels);
    printf("Sample Rate: %u\n", wav_struct.sample_rate);
    printf("Byte Rate: %u\n", wav_struct.byte_rate);
    printf("Block Align: %hu\n", wav_struct.block_align);
    printf("Bits Per Sample: %hu\n", wav_struct.bits_per_sample);
    printf("Subchunk2 ID: %.4s\n", wav_struct.subchunk2_ID);
    printf("Subchunk2 Size: %hu\n", wav_struct.subchunk2_size);
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
void calculate_the_new_data_and_write_to_output_file(wav_header_t header, FILE *input_file, FILE *output_file, double duration, char *input_filename, char *output_filename){
    // Get the number of samples and allocate memory for the audio data
    uint32_t num_samples = header.subchunk2_size / sizeof(int16_t);
    int16_t *data;
    data = malloc(num_samples * sizeof(int16_t));
    fread(data, sizeof(int16_t), num_samples, input_file);

    // Determine the number of samples of silence to add
    uint32_t silenceLen = (uint32_t)(duration * header.sample_rate);

    // Append the digital silence samples to the end of the audio data
    data = realloc(data, (num_samples + silenceLen) * sizeof(int16_t));
    memset(&data[num_samples], 0, silenceLen * sizeof(int16_t));

    // Update the WAV header with the new file size
    header.chunk_size = 36 + num_samples * sizeof(int16_t) + silenceLen * sizeof(int16_t);
    header.subchunk2_size = num_samples * sizeof(int16_t) + silenceLen * sizeof(int16_t);

    // Write the WAV header and audio data to the output file
    fwrite(&header, sizeof(wav_header_t), 1, output_file);
    fwrite(data, sizeof(int16_t), num_samples + silenceLen, output_file);

    free_resources(input_file, output_file, data);
}
void free_resources(FILE *input_file, FILE *output_file, int16_t *data){
    // Close the input and output files
    fclose(input_file);
    fclose(output_file);
    // Free the memory allocated for the audio data
    free(data);
}