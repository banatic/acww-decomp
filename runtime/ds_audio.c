/* Hardware formats and timing: GBATEK, DS Sound. The SDK sequencer supplies the envelopes. */
#include "ds_audio.h"
#include <string.h>

static const int steps[89] = {
    7,    8,    9,    10,   11,    12,    13,    14,    16,    17,    19,    21,    23,    25,    28,    31,    34,   37,
    41,   45,   50,   55,   60,    66,    73,    80,    88,    97,    107,   118,   130,   143,   157,   173,   190,  209,
    230,  253,  279,  307,  337,   371,   408,   449,   494,   544,   598,   658,   724,   796,   876,   963,   1060, 1166,
    1282, 1411, 1552, 1707, 1878,  2066,  2272,  2499,  2749,  3024,  3327,  3660,  4026,  4428,  4871,  5358,  5894, 6484,
    7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899, 15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767};
static const int index_delta[8] = {-1, -1, -1, -1, 2, 4, 6, 8};

static int clamp(int value, int low, int high)
{
    return value < low ? low : value > high ? high : value;
}

static unsigned scale(unsigned value)
{
    value &= 127;
    return value == 127 ? 128 : value;
}

void ds_audio_init(DsAudio *a, DsAudioRead read, DsAudioEmit emit, void *user)
{
    memset(a, 0, sizeof(*a));
    a->master = 127;
    a->read = read;
    a->emit = emit;
    a->user = user;
}

void ds_audio_setup(DsAudio *a, unsigned no, uint32_t control, uint32_t source, uint32_t period, uint32_t loop_words,
                    uint32_t length_words)
{
    if (no >= 16) {
        return;
    }
    DsAudioChannel *c = &a->channel[no];
    memset(c, 0, sizeof(*c));
    c->control = control & ~0x80000000u;
    c->source = source & ~3u;
    c->period = 2 * ((period & 65535u) != 0 ? period & 65535u : 65536u);
    c->loop = loop_words & 65535;
    c->length = length_words & 0x3fffff;
}

void ds_audio_start(DsAudio *a, unsigned no)
{
    if (no >= 16) {
        return;
    }
    DsAudioChannel *c = &a->channel[no];
    if (c->active) {
        return;
    }
    c->active = 1;
    c->holding = 0;
    c->phase = c->index = 0;
    c->sample = 0;
    c->psg = c->loop_saved = 0;
    c->noise = 0x7fff;
    unsigned format = c->control >> 29 & 3;
    a->started[format]++;
    c->delay = format == 3 ? 1 : format == 2 ? 11 : 3;
    if (format == 2) {
        c->predictor = (int16_t) (a->read(a->user, c->source) | a->read(a->user, c->source + 1) << 8);
        c->step_index = clamp(a->read(a->user, c->source + 2) & 127, 0, 88);
    }
}

void ds_audio_stop(DsAudio *a, unsigned no, int hold)
{
    if (no < 16) {
        a->channel[no].active = 0;
        a->channel[no].holding = hold != 0;
        if (!hold) {
            a->channel[no].sample = 0;
        }
    }
}

void ds_audio_timer(DsAudio *a, unsigned no, uint32_t period)
{
    if (no < 16) {
        a->channel[no].period = 2 * ((period & 65535u) != 0 ? period & 65535u : 65536u);
    }
}

void ds_audio_volume(DsAudio *a, unsigned no, unsigned volume, unsigned divider)
{
    if (no < 16) {
        a->channel[no].control = (a->channel[no].control & ~0x37fu) | (volume & 127) | (divider & 3) << 8;
    }
}

void ds_audio_pan(DsAudio *a, unsigned no, unsigned pan)
{
    if (no < 16) {
        a->channel[no].control = (a->channel[no].control & ~0x7f0000u) | (pan & 127) << 16;
    }
}

static void sample_next(DsAudio *a, unsigned no)
{
    DsAudioChannel *c = &a->channel[no];
    if (c->delay != 0 && --c->delay != 0) {
        return;
    }
    unsigned format = c->control >> 29 & 3;
    if (format == 3) {
        if (no >= 14) {
            unsigned carry = c->noise & 1;
            c->noise = (c->noise >> 1) ^ (carry ? 0x6000 : 0);
            c->sample = carry ? -32767 : 32767;
        } else if (no >= 8) {
            unsigned duty = c->control >> 24 & 7;
            c->sample = duty != 7 && c->psg >= 7 - duty ? 32767 : -32767;
            c->psg = (c->psg + 1) & 7;
        }
        return;
    }
    uint64_t words = (uint64_t) c->loop + c->length;
    uint64_t count = format == 0 ? words * 4 : format == 1 ? words * 2 : words != 0 ? (words - 1) * 8 : 0;
    if (count == 0) {
        c->active = 0;
        c->sample = 0;
        return;
    }
    if (c->index >= count) {
        if ((c->control >> 27 & 3) == 1 && c->length != 0) {
            c->index = format == 0 ? c->loop * 4u : format == 1 ? c->loop * 2u : c->loop ? c->loop * 8u - 8 : 0;
            if (format == 2 && c->loop_saved) {
                c->predictor = c->loop_predictor;
                c->step_index = c->loop_step_index;
            }
        } else {
            ds_audio_stop(a, no, (c->control & 0x8000) != 0);
            return;
        }
    }
    if (format == 0) {
        c->sample = (int8_t) a->read(a->user, c->source + (uint32_t) c->index) * 256;
    } else if (format == 1) {
        uint32_t at = c->source + (uint32_t) c->index * 2;
        c->sample = (int16_t) (a->read(a->user, at) | a->read(a->user, at + 1) << 8);
    } else {
        uint64_t loop = c->loop ? c->loop * 8u - 8 : 0;
        if (c->index == loop && !c->loop_saved) {
            c->loop_predictor = c->predictor;
            c->loop_step_index = c->step_index;
            c->loop_saved = 1;
        }
        unsigned nibble = a->read(a->user, c->source + 4 + (uint32_t) (c->index / 2));
        nibble = nibble >> ((c->index & 1) * 4) & 15;
        int step = steps[c->step_index];
        int delta = (step >> 3) + ((nibble & 1) ? step >> 2 : 0) + ((nibble & 2) ? step >> 1 : 0) + ((nibble & 4) ? step : 0);
        c->predictor = clamp(c->predictor + ((nibble & 8) ? -delta : delta), -32767, 32767);
        c->step_index = clamp(c->step_index + index_delta[nibble & 7], 0, 88);
        c->sample = c->predictor;
    }
    c->index++;
}

static int output(const int values[16], unsigned select, unsigned exclude);

static void mix_channels(DsAudio *a, int left[16], int right[16], int raw[16])
{
    for (unsigned no = 0; no < 16; no++) {
        DsAudioChannel *c = &a->channel[no];
        unsigned divider = c->control >> 8 & 3;
        unsigned shift = divider == 3 ? 4 : divider;
        int value = (c->active || c->holding) ? c->sample : 0;
        raw[no] = value * (int) scale(c->control) / (128 << shift);
    }
    for (unsigned no = 0; no < 16; no++) {
        int value = raw[no];
        if ((no == 0 || no == 2) && a->capture[no / 2].active && (a->capture[no / 2].control & 1) && a->channel[no].active &&
            !(a->exclude & (1u << (no + 1)))) {
            value += raw[no + 1];
        }
        if ((no == 1 || no == 3) && a->capture[no / 2].active && (a->capture[no / 2].control & 1)) {
            value = 0;
        }
        unsigned pan = scale(a->channel[no].control >> 16);
        left[no] = value * (int) (128 - pan) / 128;
        right[no] = value * (int) pan / 128;
    }
}

void ds_audio_capture_setup(DsAudio *a, unsigned no, uint32_t destination, uint32_t words, unsigned control)
{
    if (no < 2) {
        a->capture[no].destination = destination & 0x07fffffcu;
        a->capture[no].length = (words & 65535) ? (words & 65535) * 4 : 4;
        a->capture[no].control = control & 15;
        a->capture[no].active = 0;
    }
}

void ds_audio_capture_start(DsAudio *a, unsigned no, int start)
{
    if (no < 2) {
        a->capture[no].active = start != 0;
        a->capture[no].position = 0;
        a->capture[no].phase = 0;
    }
}

static void capture_sample(DsAudio *a, unsigned no)
{
    if (a->write == NULL) {
        return;
    }
    int left[16], right[16], raw[16];
    mix_channels(a, left, right, raw);
    a->capture[no].samples++;
    unsigned control = a->capture[no].control;
    int value;
    if (control & 2) {
        value = raw[no * 2];
        if (control & 1) {
            value = (int16_t) (value + raw[no * 2 + 1]);
        } else if (value < 0 && raw[no * 2 + 1] < 0) {
            value = -32768;
        }
    } else {
        value = clamp(output(no == 0 ? left : right, 0, a->exclude), -32768, 32767);
    }
    uint32_t address = a->capture[no].destination + a->capture[no].position;
    if (control & 8) {
        a->write(a->user, address, (uint8_t) ((uint16_t) value >> 8));
        a->capture[no].position++;
    } else {
        a->write(a->user, address, (uint8_t) value);
        a->write(a->user, address + 1, (uint8_t) ((uint16_t) value >> 8));
        a->capture[no].position += 2;
    }
    if (a->capture[no].position >= a->capture[no].length) {
        a->capture[no].position = 0;
        if (control & 4) {
            a->capture[no].active = 0;
        }
    }
}

static void channels_to(DsAudio *a, uint64_t cycle)
{
    while (a->cycle < cycle) {
        uint64_t elapsed = cycle - a->cycle;
        for (unsigned i = 0; i < 2; i++) {
            uint32_t period = a->channel[i * 2 + 1].period;
            if (a->capture[i].active && period != 0) {
                uint64_t due = a->capture[i].phase < period ? period - a->capture[i].phase : 0;
                if (due < elapsed) {
                    elapsed = due;
                }
            }
        }
        for (unsigned no = 0; no < 16; no++) {
            DsAudioChannel *c = &a->channel[no];
            if (!c->active || c->period == 0) {
                continue;
            }
            c->phase += elapsed;
            while (c->active && c->phase >= c->period) {
                c->phase -= c->period;
                sample_next(a, no);
            }
        }
        a->cycle += elapsed;
        for (unsigned i = 0; i < 2; i++) {
            uint32_t period = a->channel[i * 2 + 1].period;
            if (a->capture[i].active && period != 0) {
                a->capture[i].phase += elapsed;
                if (a->capture[i].phase >= period) {
                    a->capture[i].phase -= period;
                    capture_sample(a, i);
                }
            }
        }
    }
}

static int output(const int values[16], unsigned select, unsigned exclude)
{
    if (select != 0) {
        return ((select & 1) ? values[1] : 0) + ((select & 2) ? values[3] : 0);
    }
    int sum = 0;
    for (unsigned no = 0; no < 16; no++) {
        if (!(exclude & (1u << no))) {
            sum += values[no];
        }
    }
    return sum;
}

void ds_audio_advance(DsAudio *a, uint64_t cycle)
{
    if (cycle < a->cycle) {
        return;
    }
    uint64_t next = (a->frames + 1) * DS_AUDIO_CLOCK / DS_AUDIO_RATE;
    while (next <= cycle) {
        channels_to(a, next);
        int left[16], right[16], raw[16];
        mix_channels(a, left, right, raw);
        int l = output(left, a->left, a->exclude) * (int) scale(a->master) / 128;
        int r = output(right, a->right, a->exclude) * (int) scale(a->master) / 128;
        a->emit(a->user, (int16_t) clamp(l, -32768, 32767), (int16_t) clamp(r, -32768, 32767));
        a->frames++;
        next = (a->frames + 1) * DS_AUDIO_CLOCK / DS_AUDIO_RATE;
    }
    channels_to(a, cycle);
}
