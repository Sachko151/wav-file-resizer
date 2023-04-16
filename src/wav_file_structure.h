#ifndef __WAV_FILE_STRUCTURE__
#define __WAV_FILE_STRUCTURE__
#include <stdint.h>
typedef struct {
    char chunk_id[4]; //4 bytes contains "RIFF" endian: big
    uint32_t chunk_size; //4 bytes ChunkSize endian: little
    char format[4]; //4 bytes contains "WAVE" endian: big
    char subchunk1_ID[4]; //4 bytes contains "fmt" endian: big
    uint32_t subchunk1_size; // 2 rest of size endian: little
    uint16_t audio_format; //2 bytes form of compression 1:PCM, 6:A-Law, 7:Mu-Law endian: little
    uint16_t num_channels; //2 bytes Mono = 1, Stereo = 2 endian: little
    uint32_t sample_rate;   //4 bytes 8000, 44100 endian: little
    uint32_t byte_rate; //4 bytes =  SampleRate * NumChannels * BitsPerSample/8 endian: little 
    uint16_t block_align;   //2 bytes NumChannels * BitsPerSample/8 endian: little
    uint16_t bits_per_sample;   //2 bytes 8 bits = 8, 16 bits = 16 endian: little
    char subchunk2_ID[4];   //4 bytes contains "data" endian: big
    uint32_t subchunk2_size; //4 bytes NumSamples * NumChannels * BitsPerSample/8
} wav_header_t;
#endif