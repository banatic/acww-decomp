#ifndef RUNTIME_SOUND_H
#define RUNTIME_SOUND_H
#include "ds_audio.h"
#include <stdio.h>

/* Optional host output: RUN_AUDIO=1 opens the device, RUN_AUDIO_WAV writes a new WAV. */
void sound_init(DsAudioRead read, DsAudioWrite write, void *user);
DsAudio *sound_mixer(void);
void sound_advance(uint64_t cycle);
/* The window calls this on the emulation thread. WAV recording keeps emulated time. */
void sound_fast(int fast);
void sound_report(FILE *out);
#endif
