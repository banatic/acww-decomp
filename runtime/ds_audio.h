/* Bus-clocked DS sound channels. No ROM data, platform device or wall clock is owned here. */
#ifndef RUNTIME_DS_AUDIO_H
#define RUNTIME_DS_AUDIO_H
#include <stdint.h>

#define DS_AUDIO_RATE 32768u
#define DS_AUDIO_CLOCK 33513982u

typedef uint8_t (*DsAudioRead)(void *user, uint32_t address);
typedef void (*DsAudioWrite)(void *user, uint32_t address, uint8_t value);
typedef void (*DsAudioEmit)(void *user, int16_t left, int16_t right);

typedef struct DsAudioChannel {
    uint32_t control, source, period, loop, length;
    uint64_t phase, index;
    int sample, predictor, step_index, loop_predictor, loop_step_index;
    unsigned delay, active, holding, loop_saved, psg, noise;
} DsAudioChannel;

typedef struct DsAudio {
    DsAudioChannel channel[16];
    uint64_t cycle, frames, started[4];
    unsigned master, left, right, exclude;
    DsAudioRead read;
    DsAudioWrite write;
    DsAudioEmit emit;
    void *user;
    struct {
        uint32_t destination, length, position, control;
        uint64_t phase, samples;
        unsigned active;
    } capture[2];
} DsAudio;

void ds_audio_init(DsAudio *audio, DsAudioRead read, DsAudioEmit emit, void *user);
/* Call advance before changing any channel or master setting at that bus cycle. */
void ds_audio_advance(DsAudio *audio, uint64_t cycle);
void ds_audio_setup(DsAudio *audio, unsigned no, uint32_t control, uint32_t source, uint32_t period, uint32_t loop_words,
                    uint32_t length_words);
void ds_audio_start(DsAudio *audio, unsigned no);
void ds_audio_stop(DsAudio *audio, unsigned no, int hold);
void ds_audio_timer(DsAudio *audio, unsigned no, uint32_t period);
void ds_audio_volume(DsAudio *audio, unsigned no, unsigned volume, unsigned divider);
void ds_audio_pan(DsAudio *audio, unsigned no, unsigned pan);
void ds_audio_capture_setup(DsAudio *audio, unsigned no, uint32_t destination, uint32_t words, unsigned control);
void ds_audio_capture_start(DsAudio *audio, unsigned no, int start);

#endif
