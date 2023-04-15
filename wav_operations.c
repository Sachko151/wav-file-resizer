#include "wav_operations.h"
FILE *open_wav_file_and_return_error_if_encountered(char *filename){
    FILE *file_pointer = fopen(filename, "rb");
    if (file_pointer == NULL) {
        fprintf(stderr, "Error opening file\n");
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
    printf("Subchunk2 Size: %hu\n", wav_struct.subchunk1_size);
}