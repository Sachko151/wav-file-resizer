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
typedef struct
{
    // char list_id[4]; //4 bytes contains LIST
    // uint32_t overall_size; // 4 bytes contains size   // not neeeded
    // char info[4]; //4 bytes contains info
    char name_flag[4]; //4 bytes contains INAM if Track Title is present
    uint32_t name_len; //4 bytes contains length of track title
    char *track_title; //contains Track Title
    char album_flag[4]; //4 bytes contains IPRD if Album Name is specified
    uint32_t album_len; //4 bytes contains length of Album name string
    char *album_name; // contains Album Name
    char artist_flag[4]; //4 bytes contains IART if Artist Name is specified
    uint32_t artist_len; //4 bytes contains length of Artist name string
    char *artist_name; // contains Artist Name
    char comment_flag[4]; //4 bytes contains ICMT if a Comment is specified
    uint32_t comment_len; //4 bytes contains length of comment string
    char *comment; // contains comment data
    char year_flag[4]; //4 bytes contains ICRD if a Year is specified
    uint32_t year_len; //4 bytes contains length of year string
    char *year; // contains year data
    char genre_flag[4]; //4 bytes contains IGNR if a genre is specified
    uint32_t genre_len; //4 bytes contains length of genre string
    char *genre; // contains genre data
    char track_flag[4]; //4 bytes contains ITRK if a track count is specified
    uint32_t track_len; //4 bytes contains length of track count string
    char *track_count_data; // contains track count data data
} wav_additional_data_t;
#endif