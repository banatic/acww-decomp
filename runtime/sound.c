/* Host sinks for the deterministic DS mixer. Only the playable Windows build uses WinMM. */
#include "sound.h"
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) && defined(RUN_FRONT_END)
#include <windows.h>
#include <mmsystem.h>
#define SOUND_DEVICE 1
#endif

#define BLOCK_FRAMES 512
#define DEVICE_BLOCKS 8

static struct {
    DsAudio mixer;
    DsAudioRead read;
    DsAudioWrite write;
    void *user;
    FILE *wav;
    uint64_t bytes, nonzero, frames, blocks, dropped;
    int on, fast, peak, error;
    unsigned used;
    int16_t block[BLOCK_FRAMES * 2];
#ifdef SOUND_DEVICE
    HWAVEOUT device;
    WAVEHDR headers[DEVICE_BLOCKS];
    int16_t data[DEVICE_BLOCKS][BLOCK_FRAMES * 2];
    unsigned prepared;
#endif
} sound;

static void put32(FILE *file, uint32_t value)
{
    for (unsigned i = 0; i < 4; i++) {
        fputc((int) (value >> (i * 8) & 255), file);
    }
}

static void wav_header(void)
{
    fwrite("RIFF", 1, 4, sound.wav);
    put32(sound.wav, (uint32_t) sound.bytes + 36);
    fwrite("WAVEfmt ", 1, 8, sound.wav);
    put32(sound.wav, 16);
    fwrite("\1\0\2\0", 1, 4, sound.wav);
    put32(sound.wav, DS_AUDIO_RATE);
    put32(sound.wav, DS_AUDIO_RATE * 4);
    fwrite("\4\0\20\0data", 1, 8, sound.wav);
    put32(sound.wav, (uint32_t) sound.bytes);
}

static void flush_block(void)
{
    if (sound.used == 0) {
        return;
    }
    if (sound.wav != NULL && !sound.error) {
        /* Explicit little endian output, including on big endian headless hosts. */
        unsigned char bytes[BLOCK_FRAMES * 4];
        for (unsigned i = 0; i < sound.used * 2; i++) {
            bytes[i * 2] = (unsigned char) sound.block[i];
            bytes[i * 2 + 1] = (unsigned char) ((uint16_t) sound.block[i] >> 8);
        }
        unsigned size = sound.used * 4;
        if (sound.bytes + size > UINT32_MAX - 36 || fwrite(bytes, 1, size, sound.wav) != size) {
            fputs("sound: WAV output failed or exceeded the RIFF size limit\n", stderr);
            sound.error = 1;
        } else {
            sound.bytes += size;
        }
    }
#ifdef SOUND_DEVICE
    if (sound.device != NULL && !sound.fast) {
        unsigned i;
        for (i = 0; i < sound.prepared; i++) {
            WAVEHDR *h = &sound.headers[i];
            if (!(h->dwFlags & WHDR_INQUEUE)) {
                memcpy(sound.data[i], sound.block, sound.used * 4);
                h->dwBufferLength = sound.used * 4;
                MMRESULT result = waveOutWrite(sound.device, h, sizeof(*h));
                if (result == MMSYSERR_NOERROR) {
                    sound.blocks++;
                } else {
                    sound.dropped++;
                }
                break;
            }
        }
        if (i == sound.prepared) {
            sound.dropped++;
        }
    }
#endif
    sound.used = 0;
}

static uint8_t read_byte(void *user, uint32_t address)
{
    (void) user;
    return sound.read(sound.user, address);
}

static void write_byte(void *user, uint32_t address, uint8_t value)
{
    (void) user;
    if (sound.write) {
        sound.write(sound.user, address, value);
    }
}

static void emit(void *user, int16_t left, int16_t right)
{
    (void) user;
    sound.frames++;
    sound.nonzero += left != 0 || right != 0;
    int l = left < 0 ? -(int) left : left, r = right < 0 ? -(int) right : right;
    if (l > sound.peak) {
        sound.peak = l;
    }
    if (r > sound.peak) {
        sound.peak = r;
    }
    sound.block[sound.used * 2] = left;
    sound.block[sound.used * 2 + 1] = right;
    if (++sound.used == BLOCK_FRAMES) {
        flush_block();
    }
}

static void finish(void)
{
    sound_report(stderr);
    flush_block();
    if (sound.wav != NULL) {
        if (fseek(sound.wav, 0, SEEK_SET) == 0) {
            wav_header();
        }
        if (fclose(sound.wav) != 0) {
            fputs("sound: could not close WAV output\n", stderr);
        }
        sound.wav = NULL;
    }
#ifdef SOUND_DEVICE
    if (sound.device != NULL) {
        waveOutReset(sound.device);
        for (unsigned i = 0; i < sound.prepared; i++) {
            waveOutUnprepareHeader(sound.device, &sound.headers[i], sizeof(WAVEHDR));
        }
        waveOutClose(sound.device);
        sound.device = NULL;
    }
#endif
}

void sound_init(DsAudioRead read, DsAudioWrite write, void *user)
{
    const char *enabled = getenv("RUN_AUDIO"), *path = getenv("RUN_AUDIO_WAV");
    /* Runtime initialization can occur again during replay; keep the atexit registration unique. */
    static int registered;
    finish();
    memset(&sound, 0, sizeof(sound));
    sound.on = (enabled != NULL && atoi(enabled) != 0) || (path != NULL && path[0] != 0);
    if (!sound.on) {
        return;
    }
    sound.read = read;
    sound.write = write;
    sound.user = user;
    ds_audio_init(&sound.mixer, read_byte, emit, NULL);
    sound.mixer.write = write_byte;
    if (!registered) {
        atexit(finish);
        registered = 1;
    }
    if (path != NULL && path[0] != 0) {
        sound.wav = fopen(path, "wbx");
        if (sound.wav == NULL) {
            fprintf(stderr, "sound: cannot create new WAV %s\n", path);
            exit(1);
        }
        wav_header();
    }
#ifdef SOUND_DEVICE
    if (enabled != NULL && atoi(enabled) != 0) {
        WAVEFORMATEX format = {WAVE_FORMAT_PCM, 2, DS_AUDIO_RATE, DS_AUDIO_RATE * 4, 4, 16, 0};
        MMRESULT result = waveOutOpen(&sound.device, WAVE_MAPPER, &format, 0, 0, CALLBACK_NULL);
        if (result != MMSYSERR_NOERROR) {
            sound.device = NULL;
            fprintf(stderr, "sound: cannot open Windows audio device (%u)\n", (unsigned) result);
        } else {
            for (unsigned i = 0; i < DEVICE_BLOCKS; i++) {
                WAVEHDR *h = &sound.headers[i];
                h->lpData = (LPSTR) sound.data[i];
                h->dwBufferLength = sizeof(sound.data[i]);
                if (waveOutPrepareHeader(sound.device, h, sizeof(*h)) != MMSYSERR_NOERROR) {
                    break;
                }
                sound.prepared++;
            }
            fprintf(stderr, "sound: Windows stereo PCM %u Hz, %u buffers\n", DS_AUDIO_RATE, sound.prepared);
        }
    }
#endif
}

DsAudio *sound_mixer(void)
{
    return sound.on ? &sound.mixer : NULL;
}

void sound_advance(uint64_t cycle)
{
    if (sound.on) {
        ds_audio_advance(&sound.mixer, cycle);
    }
}

void sound_fast(int fast)
{
    if (sound.fast == (fast != 0)) {
        return;
    }
    sound.fast = fast != 0;
#ifdef SOUND_DEVICE
    if (sound.device != NULL) {
        waveOutReset(sound.device);
    }
#endif
}

void sound_report(FILE *out)
{
    if (sound.on) {
        flush_block();
        fprintf(out, "sound: %llu stereo frames, %llu nonzero, peak %d; %llu device blocks, %llu dropped\n",
                (unsigned long long) sound.frames, (unsigned long long) sound.nonzero, sound.peak,
                (unsigned long long) sound.blocks, (unsigned long long) sound.dropped);
        fprintf(out, "sound: PCM8/PCM16/ADPCM/PSG starts %llu/%llu/%llu/%llu; capture samples %llu/%llu\n",
                (unsigned long long) sound.mixer.started[0], (unsigned long long) sound.mixer.started[1],
                (unsigned long long) sound.mixer.started[2], (unsigned long long) sound.mixer.started[3],
                (unsigned long long) sound.mixer.capture[0].samples, (unsigned long long) sound.mixer.capture[1].samples);
    }
}
