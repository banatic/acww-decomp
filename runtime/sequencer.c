/* The ARM7's sound sequencer; see sequencer.h.
 *
 * What is here was read from the ARM7 binary in the ROM (extract/adm-kr/arm7/arm7.bin; the
 * numbers below are offsets in that file, whose sound driver is loaded to ARM7 WRAM) and from
 * the ARM9's SDK, which reads the same structures (libs/NitroSDK/autoload_2/SND_ReadTrackInfo.c
 * and SND_ReadPlayerInfo.c name the fields). The sequence data format is the SDK's SSEQ.
 *
 * The driver's state is kept as the ARM7 keeps it, byte for byte (SNDWork, 0x1180 bytes at
 * 0x03807ecc of the ARM7's memory): 16 channels of 0x54 bytes, 16 players of 0x24 at 0x540, 32
 * tracks of 0x40 at 0x780 and 8 alarms of 0x40 at 0xf80. The ARM9 asks for a copy of it
 * (SND_COMMAND_READ_DRIVER_INFO) to read a player's tempo and a track's state, and its commands
 * write into it by offset (SND_COMMAND_PLAYER_PARAM, _TRACK_PARAM).
 *
 * Time: the ARM7's sound thread runs on a periodic alarm of 0xaa8 OS ticks (64 bus cycles a
 * tick: 5.21 ms), first 0x10000 ticks after the driver starts (0x4584), and also whenever a
 * command list comes. Each periodic pass steps every playing sequence by the ticks its tempo
 * gives (0x659c): 240 to the beat, `tempo` beats a minute, scaled by the tempo ratio / 256.
 *
 * Left out: the channels. A note takes none, so a track's channel list is always empty: a note
 * of length 0 in note-wait mode (which waits for its channel's end) ends at once, and the
 * driver's copy reports no channel for any track and the channel registers as 0. */
#include "sequencer.h"

#include <stdlib.h>
#include <string.h>

#include "io.h"

#define WORK_SIZE 0x1180u
#define WORK_ADDRESS 0x03807eccu /* where the ARM7 keeps it: SNDDriverInfo.workAddress */
#define CHANNELS 16
#define CHANNEL_SIZE 0x54u
#define PLAYERS 16
#define PLAYER_BASE 0x540u
#define PLAYER_SIZE 0x24u
#define TRACKS 32
#define TRACK_BASE 0x780u
#define TRACK_SIZE 0x40u
#define TRACKS_PER_PLAYER 16
#define NO_TRACK 0xffu

/* SNDPlayer */
#define P_FLAGS 0x00 /* bit 0 active, 1 prepared (started), 2 paused */
#define P_NO 0x01
#define P_PRIO 0x04
#define P_VOLUME 0x05
#define P_EXT_FADER 0x06
#define P_TRACKS 0x08
#define P_TEMPO 0x18
#define P_TEMPO_RATIO 0x1a
#define P_TEMPO_COUNTER 0x1c
#define P_BANK 0x20
#define PF_ACTIVE 0x01u
#define PF_PREPARED 0x02u
#define PF_PAUSE 0x04u

/* SNDTrack */
#define T_FLAGS 0x00
#define T_PAN_RANGE 0x01
#define T_PRG 0x02
#define T_VOLUME 0x04
#define T_VOLUME2 0x05
#define T_PITCH_BEND 0x06
#define T_BEND_RANGE 0x07
#define T_PAN 0x08
#define T_EXT_PAN 0x09
#define T_EXT_FADER 0x0a
#define T_EXT_PITCH 0x0c
#define T_ATTACK 0x0e
#define T_DECAY 0x0f
#define T_SUSTAIN 0x10
#define T_RELEASE 0x11
#define T_PRIO 0x12
#define T_TRANSPOSE 0x13
#define T_PORTA_KEY 0x14
#define T_PORTA_TIME 0x15
#define T_SWEEP 0x16
#define T_MOD_TARGET 0x18
#define T_MOD_SPEED 0x19
#define T_MOD_DEPTH 0x1a
#define T_MOD_RANGE 0x1b
#define T_MOD_DELAY 0x1c
#define T_CHANNEL_MASK 0x1e
#define T_WAIT 0x20
#define T_BASE 0x24
#define T_CUR 0x28
#define T_CALL_STACK 0x2c
#define T_LOOP_COUNT 0x38
#define T_DEPTH 0x3b
#define T_CHANNELS 0x3c
#define TF_ACTIVE 0x01u
#define TF_NOTE_WAIT 0x02u
#define TF_MUTE 0x04u
#define TF_TIE 0x08u
#define TF_NOTE_FINISH_WAIT 0x10u
#define TF_PORTA 0x20u
#define TF_CMP 0x40u
#define TF_CHANNEL_MASK 0x80u
#define CALL_DEPTH 3

/* The shared work (SNDSharedWork, in main RAM): the finished command tag, the player status,
 * the channel and capture status, then 16 players of 16 variables and a tick counter, then 16
 * global variables. */
#define SW_PLAYER_STATUS 0x04u
#define SW_CHANNEL_STATUS 0x08u
#define SW_CAPTURE_STATUS 0x0au
#define SW_PLAYER 0x20u
#define SW_TICKS 0x20u /* within a player's part */
#define SW_GLOBAL 0x260u

/* The ARM7's periodic alarm and its first delay, in bus cycles. */
#define PERIOD_CYCLES (0xaa8ull * 64)
#define FIRST_DELAY_CYCLES (0x10000ull * 64)
#define BASE_TEMPO 240

/* The command ids (libs/NitroSDK/autoload_2/SND_ReadDriverInfo.c's SNDCommandID). */
enum {
    CMD_START_SEQ = 0x00,
    CMD_STOP_SEQ = 0x01,
    CMD_PREPARE_SEQ = 0x02,
    CMD_START_PREPARED_SEQ = 0x03,
    CMD_PAUSE_SEQ = 0x04,
    CMD_SKIP_SEQ = 0x05,
    CMD_PLAYER_PARAM = 0x06,
    CMD_TRACK_PARAM = 0x07,
    CMD_MUTE_TRACK = 0x08,
    CMD_ALLOCATABLE_CHANNEL = 0x09,
    CMD_PLAYER_LOCAL_VAR = 0x0a,
    CMD_PLAYER_GLOBAL_VAR = 0x0b,
    CMD_LOCK_CHANNEL = 0x1a,
    CMD_UNLOCK_CHANNEL = 0x1b,
    CMD_INVALIDATE_SEQ = 0x1e,
    CMD_INVALIDATE_BANK = 0x1f,
    CMD_READ_DRIVER_INFO = 0x21,
};

static struct {
    int on;
    uint8_t work[WORK_SIZE];
    uint32_t random; /* the driver's random number state (0x41fc), 0x12345678 at the start */
    uint64_t next_period;
    uint32_t locked, locked_weak; /* the channels locked by the ARM9 (strong, weak) */
    uint32_t shared_work;         /* as the command being run sees it */
    uint64_t periods, ticks, started, finished, commands;
} sq;

/* --- the driver's state, by offset --- */

static uint32_t w8(uint32_t o)
{
    return sq.work[o];
}

static uint32_t w16(uint32_t o)
{
    return (uint32_t) sq.work[o] | (uint32_t) sq.work[o + 1] << 8;
}

static uint32_t w32(uint32_t o)
{
    return w16(o) | w16(o + 2) << 16;
}

static void set8(uint32_t o, uint32_t v)
{
    sq.work[o] = (uint8_t) v;
}

static void set16(uint32_t o, uint32_t v)
{
    set8(o, v);
    set8(o + 1, v >> 8);
}

static void set32(uint32_t o, uint32_t v)
{
    set16(o, v);
    set16(o + 2, v >> 16);
}

/* A store of `size` bytes (1, 2 or 4; another size stores nothing), as the parameter
 * commands make. */
static void set_sized(uint32_t o, uint32_t v, uint32_t size)
{
    if (o + size > WORK_SIZE) {
        return;
    }
    if (size == 1) {
        set8(o, v);
    } else if (size == 2) {
        set16(o, v);
    } else if (size == 4) {
        set32(o, v);
    }
}

static uint32_t player_at(uint32_t no)
{
    return PLAYER_BASE + (no & 0xf) * PLAYER_SIZE;
}

static uint32_t track_at(uint32_t id)
{
    return TRACK_BASE + (id & 0x1f) * TRACK_SIZE;
}

/* The player's track `i`, or 0 when it has none (0x6570). */
static uint32_t player_track(uint32_t p, uint32_t i)
{
    if (i >= TRACKS_PER_PLAYER) {
        return 0;
    }
    uint32_t id = w8(p + P_TRACKS + i);
    return id == NO_TRACK ? 0 : track_at(id);
}

static int has(uint32_t o, uint32_t flag)
{
    return (w8(o) & flag) != 0;
}

static void set_flag(uint32_t o, uint32_t flag, int value)
{
    set8(o, value ? (w8(o) | flag) : (w8(o) & ~flag));
}

/* --- the ARM9's memory --- */

static uint32_t guest8(uint32_t a)
{
    uint32_t v = 0;
    bus_read(a, 1, &v);
    return v & 0xff;
}

static uint32_t guest16(uint32_t a)
{
    uint32_t v = 0;
    bus_read(a, 2, &v);
    return v & 0xffff;
}

static void guest_store16(uint32_t a, uint32_t v)
{
    bus_write(a, 2, v & 0xffff);
}

static void guest_store32(uint32_t a, uint32_t v)
{
    bus_write(a, 4, v);
}

/* The address of variable `index` of player `p` (0-15: the player's own; 16 and on: the global
 * ones, without a bound, as 0x564c has it), or 0 without a shared work. */
static uint32_t variable(uint32_t p, uint32_t index)
{
    if (sq.shared_work == 0) {
        return 0;
    }
    if (index >= 16) {
        return sq.shared_work + SW_GLOBAL + (index - 16) * 2;
    }
    return sq.shared_work + SW_PLAYER + w8(p + P_NO) * PLAYER_SIZE + index * 2;
}

/* The driver's random numbers (0x41fc): a linear congruential generator, its top half. */
static uint32_t random16(void)
{
    sq.random = sq.random * 1664525u + 1013904223u;
    return sq.random >> 16;
}

/* --- reading a track's sequence --- */

static uint32_t next_byte(uint32_t t)
{
    uint32_t cur = w32(t + T_CUR);
    set32(t + T_CUR, cur + 1);
    return guest8(cur);
}

static uint32_t next_u16(uint32_t t)
{
    uint32_t lo = next_byte(t);
    return lo | next_byte(t) << 8;
}

static uint32_t next_u24(uint32_t t)
{
    uint32_t v = next_byte(t);
    v |= next_byte(t) << 8;
    return v | next_byte(t) << 16;
}

static uint32_t next_varlen(uint32_t t)
{
    uint32_t v = 0, b;
    do {
        b = next_byte(t);
        v = (v << 7) | (b & 0x7f);
    } while (b & 0x80);
    return v;
}

/* An argument of `kind` (0x68c0): 0 a byte, 1 a halfword, 2 a variable-length number, 3 a
 * random number between two signed halfwords, 4 a variable's value. */
enum { ARG_U8, ARG_U16, ARG_VARLEN, ARG_RANDOM, ARG_VARIABLE };

static int32_t next_arg(uint32_t t, uint32_t p, int kind)
{
    switch (kind) {
        case ARG_U8:
            return (int32_t) next_byte(t);
        case ARG_U16:
            return (int32_t) next_u16(t);
        case ARG_VARLEN:
            return (int32_t) next_varlen(t);
        case ARG_RANDOM: {
            int32_t low = (int16_t) next_u16(t);
            int32_t high = (int16_t) next_u16(t);
            /* the product wraps as the ARM's does */
            return ((int32_t) (random16() * (uint32_t) (high - low + 1)) >> 16) + low;
        }
        case ARG_VARIABLE: {
            uint32_t a = variable(p, next_byte(t));
            /* the ROM leaves a stale register without a shared work; 0 here */
            return a != 0 ? (int16_t) guest16(a) : 0;
        }
        default:
            return 0;
    }
}

/* --- tracks and players --- */

/* A track's set-up (0x67cc). */
static void track_init(uint32_t t)
{
    set32(t + T_BASE, 0);
    set32(t + T_CUR, 0);
    uint32_t flags = (w8(t) & TF_ACTIVE) | TF_NOTE_WAIT | TF_CMP;
    set8(t + T_FLAGS, flags);
    set8(t + T_DEPTH, 0);
    set16(t + T_PRG, 0);
    set8(t + T_PRIO, 0x40);
    set8(t + T_VOLUME, 0x7f);
    set8(t + T_VOLUME2, 0x7f);
    set16(t + T_EXT_FADER, 0);
    set8(t + T_PAN, 0);
    set8(t + T_EXT_PAN, 0);
    set8(t + T_PITCH_BEND, 0);
    set16(t + T_EXT_PITCH, 0);
    set8(t + T_ATTACK, 0xff);
    set8(t + T_DECAY, 0xff);
    set8(t + T_SUSTAIN, 0xff);
    set8(t + T_RELEASE, 0xff);
    set8(t + T_PAN_RANGE, 0x7f);
    set8(t + T_BEND_RANGE, 2);
    set8(t + T_PORTA_KEY, 60);
    set8(t + T_PORTA_TIME, 0);
    set16(t + T_SWEEP, 0);
    set8(t + T_TRANSPOSE, 0);
    set16(t + T_CHANNEL_MASK, 0xffff);
    /* the modulation (0x4a8c): target 0, speed 16, depth 0, range 1, delay 0 */
    set8(t + T_MOD_TARGET, 0);
    set8(t + T_MOD_DEPTH, 0);
    set8(t + T_MOD_RANGE, 1);
    set8(t + T_MOD_SPEED, 0x10);
    set16(t + T_MOD_DELAY, 0);
    set32(t + T_WAIT, 0);
    set32(t + T_CHANNELS, 0);
}

/* The first free track, taken (0x5608); -1 when there is none. */
static int track_alloc(void)
{
    for (int id = 0; id < TRACKS; id++) {
        uint32_t t = track_at((uint32_t) id);
        if (!has(t, TF_ACTIVE)) {
            set_flag(t, TF_ACTIVE, 1);
            return id;
        }
    }
    return -1;
}

/* The player's track `i` closed (0x64fc): its channels released (it has none), the track freed. */
static void track_close(uint32_t p, uint32_t i)
{
    uint32_t t = player_track(p, i);
    if (t == 0) {
        return;
    }
    set_flag(t, TF_ACTIVE, 0);
    set8(p + P_TRACKS + i, NO_TRACK);
}

/* The player stopped (0x64bc): every track closed, the player inactive. */
static void player_stop(uint32_t p)
{
    for (uint32_t i = 0; i < TRACKS_PER_PLAYER; i++) {
        track_close(p, i);
    }
    set_flag(p, PF_ACTIVE, 0);
}

/* The player's set-up for a new sequence (0x6708). */
static void player_init(uint32_t p, uint32_t bank)
{
    set_flag(p, PF_PAUSE, 0);
    set32(p + P_BANK, bank);
    set16(p + P_TEMPO, 120);
    set16(p + P_TEMPO_RATIO, 0x100);
    set16(p + P_TEMPO_COUNTER, BASE_TEMPO);
    set8(p + P_VOLUME, 0x7f);
    set16(p + P_EXT_FADER, 0);
    set8(p + P_PRIO, 0x40);
    for (uint32_t i = 0; i < TRACKS_PER_PLAYER; i++) {
        set8(p + P_TRACKS + i, NO_TRACK);
    }
    if (sq.shared_work != 0) {
        uint32_t own = sq.shared_work + SW_PLAYER + w8(p + P_NO) * PLAYER_SIZE;
        guest_store32(own + SW_TICKS, 0);
        for (uint32_t i = 0; i < 16; i++) {
            guest_store16(own + i * 2, 0xffff);
        }
    }
}

static void status_bit(uint32_t no, int on)
{
    if (sq.shared_work == 0) {
        return;
    }
    uint32_t v = 0;
    bus_read(sq.shared_work + SW_PLAYER_STATUS, 4, &v);
    v = on ? (v | 1u << no) : (v & ~(1u << no));
    guest_store32(sq.shared_work + SW_PLAYER_STATUS, v);
}

/* A sequence prepared on player `no` (0x6fec): from `base` + `offset`, a first track, and when
 * the sequence opens with 0xfe the tracks its mask names (bit 1 for track 1 and so on). */
static void prepare(uint32_t no, uint32_t base, uint32_t offset, uint32_t bank)
{
    uint32_t p = player_at(no);
    if (has(p, PF_ACTIVE)) {
        player_stop(p);
    }
    player_init(p, bank);
    int id = track_alloc();
    if (id < 0) {
        return;
    }
    uint32_t t = track_at((uint32_t) id);
    track_init(t);
    set32(t + T_BASE, base);
    set32(t + T_CUR, base + offset);
    set8(p + P_TRACKS, (uint32_t) id);
    if (next_byte(t) == 0xfe) {
        uint32_t mask = (next_u16(t) & 0xffff) >> 1;
        for (uint32_t i = 1; mask != 0; i++, mask >>= 1) {
            if (mask & 1) {
                int other = track_alloc();
                if (other < 0) {
                    break;
                }
                track_init(track_at((uint32_t) other));
                set8(p + P_TRACKS + i, (uint32_t) other);
            }
        }
    } else {
        set32(t + T_CUR, w32(t + T_CUR) - 1);
    }
    set_flag(p, PF_ACTIVE, 1);
    set_flag(p, PF_PREPARED, 0);
    status_bit(no, 1);
    sq.started++;
}

/* The comparisons of commands 0xb8-0xbd. */
static int compare(uint32_t op, int32_t a, int32_t b)
{
    switch (op) {
        case 0xb8:
            return a == b;
        case 0xb9:
            return a >= b;
        case 0xba:
            return a > b;
        case 0xbb:
            return a <= b;
        case 0xbc:
            return a < b;
        default:
            return a != b;
    }
}

/* A variable command (0xb0-0xbd) on the variable at `a`. */
static void variable_op(uint32_t t, uint32_t op, uint32_t a, int32_t v)
{
    int32_t x = (int16_t) guest16(a);
    switch (op) {
        case 0xb0:
            x = v;
            break;
        case 0xb1:
            x += v;
            break;
        case 0xb2:
            x -= v;
            break;
        case 0xb3:
            x *= v;
            break;
        case 0xb4:
            if (v == 0) {
                return;
            }
            x /= v;
            break;
        case 0xb5:
            if (v >= 0) { /* as the ARM shifts: by 32 or more, every bit out */
                x = v >= 32 ? 0 : (int32_t) ((uint32_t) x << v);
            } else {
                x = -v >= 32 ? (x < 0 ? -1 : 0) : x >> -v;
            }
            break;
        case 0xb6: {
            int negative = v < 0;
            if (negative) {
                v = (int16_t) -v;
            }
            x = (int32_t) (random16() * (uint32_t) (v + 1)) >> 16;
            if (negative) {
                x = -x;
            }
            break;
        }
        case 0xb7:
            return;
        default:
            set_flag(t, TF_CMP, compare(op, x, v));
            return;
    }
    guest_store16(a, (uint32_t) x);
}

/* One tick of track `t`, player `p`'s (0x5710): its wait counted down and, once it is over,
 * its commands run up to the next wait. `play` is 0 when skipping (no note sounds). Returns
 * -1 when the track ends (0xff), else 0. */
static int track_tick(uint32_t p, uint32_t t, int play)
{
    (void) play; /* notes take no channel here, played or not */
    if (has(t, TF_NOTE_FINISH_WAIT)) {
        if (w32(t + T_CHANNELS) != 0) {
            return 0;
        }
        set_flag(t, TF_NOTE_FINISH_WAIT, 0);
    }
    int32_t wait = (int32_t) w32(t + T_WAIT);
    if (wait > 0) {
        set32(t + T_WAIT, (uint32_t) (wait - 1));
        if (wait - 1 > 0) {
            return 0;
        }
    }
    while (w32(t + T_WAIT) == 0 && !has(t, TF_NOTE_FINISH_WAIT)) {
        int kind = -1; /* the argument kind a prefix asks for */
        int run = 1;   /* 0 under 0xa2 with the comparison false: read, not done */
        uint32_t c = next_byte(t);
        if (c == 0xa2) {
            c = next_byte(t);
            run = has(t, TF_CMP);
        }
        if (c == 0xa0) {
            c = next_byte(t);
            kind = ARG_RANDOM;
        }
        if (c == 0xa1) {
            c = next_byte(t);
            kind = ARG_VARIABLE;
        }
        if (!(c & 0x80)) { /* a note: key c, velocity, length */
            next_byte(t);
            int32_t length = next_arg(t, p, kind >= 0 ? kind : ARG_VARLEN);
            int32_t key = (int32_t) c + (int8_t) w8(t + T_TRANSPOSE);
            if (!run) {
                continue;
            }
            key = key < 0 ? 0 : key > 127 ? 127 : key;
            set8(t + T_PORTA_KEY, (uint32_t) key);
            if (has(t, TF_NOTE_WAIT)) {
                set32(t + T_WAIT, (uint32_t) length);
                if (length == 0) {
                    set_flag(t, TF_NOTE_FINISH_WAIT, 1);
                }
            }
            continue;
        }
        switch (c & 0xf0) {
            case 0x80: {
                int32_t v = next_arg(t, p, kind >= 0 ? kind : ARG_VARLEN);
                if (!run) {
                    break;
                }
                if (c == 0x80) {
                    set32(t + T_WAIT, (uint32_t) v);
                } else if (c == 0x81 && v < 0x10000) {
                    set16(t + T_PRG, (uint32_t) v);
                }
                break;
            }
            case 0x90:
                if (c == 0x93) {
                    uint32_t i = next_byte(t);
                    uint32_t offset = next_u24(t);
                    uint32_t other = run ? player_track(p, i) : 0;
                    if (other != 0 && other != t) {
                        set32(other + T_BASE, w32(t + T_BASE));
                        set32(other + T_CUR, w32(t + T_BASE) + offset);
                    }
                } else if (c == 0x94) {
                    uint32_t offset = next_u24(t);
                    if (run) {
                        set32(t + T_CUR, w32(t + T_BASE) + offset);
                    }
                } else if (c == 0x95) {
                    uint32_t offset = next_u24(t);
                    uint32_t depth = w8(t + T_DEPTH);
                    if (run && depth < CALL_DEPTH) {
                        set32(t + T_CALL_STACK + depth * 4, w32(t + T_CUR));
                        set8(t + T_DEPTH, depth + 1);
                        set32(t + T_CUR, w32(t + T_BASE) + offset);
                    }
                }
                break;
            case 0xc0:
            case 0xd0: {
                uint32_t v = (uint32_t) next_arg(t, p, kind >= 0 ? kind : ARG_U8) & 0xff;
                if (!run) {
                    break;
                }
                switch (c) {
                    case 0xc0:
                        set8(t + T_PAN, v - 0x40);
                        break;
                    case 0xc1:
                        set8(t + T_VOLUME, v);
                        break;
                    case 0xc2:
                        set8(p + P_VOLUME, v);
                        break;
                    case 0xc3:
                        set8(t + T_TRANSPOSE, v);
                        break;
                    case 0xc4:
                        set8(t + T_PITCH_BEND, v);
                        break;
                    case 0xc5:
                        set8(t + T_BEND_RANGE, v);
                        break;
                    case 0xc6:
                        set8(t + T_PRIO, v);
                        break;
                    case 0xc7:
                        set_flag(t, TF_NOTE_WAIT, v & 1);
                        break;
                    case 0xc8: /* tie; the channels released (there are none) */
                        set_flag(t, TF_TIE, v & 1);
                        set32(t + T_CHANNELS, 0);
                        break;
                    case 0xc9:
                        set8(t + T_PORTA_KEY, v + (uint32_t) (int8_t) w8(t + T_TRANSPOSE));
                        set_flag(t, TF_PORTA, 1);
                        break;
                    case 0xca:
                        set8(t + T_MOD_DEPTH, v);
                        break;
                    case 0xcb:
                        set8(t + T_MOD_SPEED, v);
                        break;
                    case 0xcc:
                        set8(t + T_MOD_TARGET, v);
                        break;
                    case 0xcd:
                        set8(t + T_MOD_RANGE, v);
                        break;
                    case 0xce:
                        set_flag(t, TF_PORTA, v & 1);
                        break;
                    case 0xcf:
                        set8(t + T_PORTA_TIME, v);
                        break;
                    case 0xd0:
                        set8(t + T_ATTACK, v);
                        break;
                    case 0xd1:
                        set8(t + T_DECAY, v);
                        break;
                    case 0xd2:
                        set8(t + T_SUSTAIN, v);
                        break;
                    case 0xd3:
                        set8(t + T_RELEASE, v);
                        break;
                    case 0xd4: { /* loop start: `v` times, 0 for ever */
                        uint32_t depth = w8(t + T_DEPTH);
                        if (depth < CALL_DEPTH) {
                            set32(t + T_CALL_STACK + depth * 4, w32(t + T_CUR));
                            set8(t + T_LOOP_COUNT + depth, v);
                            set8(t + T_DEPTH, depth + 1);
                        }
                        break;
                    }
                    case 0xd5:
                        set8(t + T_VOLUME2, v);
                        break;
                    default: /* 0xd6, a variable printed by a debug driver, and the unused ones */
                        break;
                }
                break;
            }
            case 0xe0: {
                uint32_t v = (uint32_t) next_arg(t, p, kind >= 0 ? kind : ARG_U16) & 0xffff;
                if (!run) {
                    break;
                }
                if (c == 0xe0) {
                    set16(t + T_MOD_DELAY, v);
                } else if (c == 0xe1) {
                    set16(p + P_TEMPO, v);
                } else if (c == 0xe3) {
                    set16(t + T_SWEEP, v);
                }
                break;
            }
            case 0xb0: {
                uint32_t index = next_byte(t);
                int32_t v = (int16_t) next_arg(t, p, kind >= 0 ? kind : ARG_U16);
                uint32_t a = variable(p, index);
                if (run && a != 0) {
                    variable_op(t, c, a, v);
                }
                break;
            }
            case 0xf0:
                if (!run) {
                    break;
                }
                if (c == 0xfc) { /* loop end */
                    uint32_t depth = w8(t + T_DEPTH);
                    if (depth == 0) {
                        break;
                    }
                    uint32_t count = w8(t + T_LOOP_COUNT + depth - 1);
                    if (count != 0 && --count == 0) {
                        set8(t + T_DEPTH, depth - 1);
                        break;
                    }
                    set8(t + T_LOOP_COUNT + depth - 1, count);
                    set32(t + T_CUR, w32(t + T_CALL_STACK + (depth - 1) * 4));
                } else if (c == 0xfd) { /* return */
                    uint32_t depth = w8(t + T_DEPTH);
                    if (depth != 0) {
                        set8(t + T_DEPTH, depth - 1);
                        set32(t + T_CUR, w32(t + T_CALL_STACK + (depth - 1) * 4));
                    }
                } else if (c == 0xff) {
                    return -1;
                }
                break;
            default:
                break;
        }
    }
    return 0;
}

/* One tick of every track of the player (0x5690); 1 when none goes on. */
static int player_tick(uint32_t p, int play)
{
    int going = 0;
    for (uint32_t i = 0; i < TRACKS_PER_PLAYER; i++) {
        uint32_t t = player_track(p, i);
        if (t == 0 || w32(t + T_CUR) == 0) {
            continue;
        }
        if (track_tick(p, t, play) == 0) {
            going = 1;
        } else {
            track_close(p, i);
        }
    }
    return !going;
}

static void add_ticks(uint32_t p, uint32_t n)
{
    if (sq.shared_work == 0) {
        return;
    }
    uint32_t a = sq.shared_work + SW_PLAYER + w8(p + P_NO) * PLAYER_SIZE + SW_TICKS, v = 0;
    bus_read(a, 4, &v);
    guest_store32(a, v + n);
    sq.ticks += n;
}

/* The periodic pass's steps of a player (0x659c): a tick for every 240 of its tempo counter,
 * then the counter raised by the tempo times the ratio / 256. */
static void player_main(uint32_t p)
{
    uint32_t due = 0, done = 0;
    while (w16(p + P_TEMPO_COUNTER) >= BASE_TEMPO) {
        set16(p + P_TEMPO_COUNTER, w16(p + P_TEMPO_COUNTER) - BASE_TEMPO);
        due++;
    }
    for (; done < due; done++) {
        if (player_tick(p, 1)) {
            player_stop(p);
            sq.finished++;
            break;
        }
    }
    add_ticks(p, done);
    uint32_t step = (uint32_t) ((int32_t) (w16(p + P_TEMPO) * w16(p + P_TEMPO_RATIO)) >> 8);
    set16(p + P_TEMPO_COUNTER, w16(p + P_TEMPO_COUNTER) + step);
}

/* The sequencer's pass (0x7140): the started players stepped on a periodic pass unless paused,
 * then the shared work told which players are active. */
static void seq_main(int periodic)
{
    uint32_t status = 0;
    for (uint32_t no = 0; no < PLAYERS; no++) {
        uint32_t p = player_at(no);
        if (!has(p, PF_ACTIVE)) {
            continue;
        }
        if (has(p, PF_PREPARED) && periodic && !has(p, PF_PAUSE)) {
            player_main(p);
        }
        if (has(p, PF_ACTIVE)) {
            status |= 1u << no;
        }
    }
    if (sq.shared_work != 0) {
        guest_store32(sq.shared_work + SW_PLAYER_STATUS, status);
    }
}

/* The rest of a pass of the sound thread (0x4494): the shared work's channel and capture
 * status (nothing sounds), and a random number drawn. */
static void thread_pass(int periodic)
{
    seq_main(periodic);
    if (sq.shared_work != 0) {
        guest_store16(sq.shared_work + SW_CHANNEL_STATUS, 0);
        guest_store16(sq.shared_work + SW_CAPTURE_STATUS, 0);
    }
    random16();
}

/* Driver info (0x781c): the state, where the ARM7 keeps it, each channel's control register
 * (none sounds: 0) and the channels locked. */
static void read_driver_info(uint32_t to)
{
    for (uint32_t i = 0; i < WORK_SIZE; i += 4) {
        guest_store32(to + i, w32(i));
    }
    for (uint32_t i = 0; i < CHANNELS; i++) {
        guest_store32(to + WORK_SIZE + i * 4, 0);
    }
    guest_store32(to + WORK_SIZE + 0x40, WORK_ADDRESS);
    guest_store32(to + WORK_SIZE + 0x44, sq.locked);
}

int sequencer_init(void)
{
    const char *v = getenv("RUN_SEQUENCER");
    memset(&sq, 0, sizeof sq);
    sq.on = v != NULL && atoi(v) != 0;
    sq.random = 0x12345678u;
    sq.next_period = FIRST_DELAY_CYCLES;
    for (uint32_t i = 0; i < CHANNELS; i++) {
        set8(i * CHANNEL_SIZE, i); /* the channels' numbers (0x55a8) */
    }
    for (uint32_t no = 0; no < PLAYERS; no++) {
        set8(player_at(no) + P_NO, no); /* the players' (0x71e0) */
    }
    return sq.on;
}

void sequencer_command(uint32_t id, const uint32_t args[4], uint32_t shared_work)
{
    sq.shared_work = shared_work;
    sq.commands++;
    switch (id) {
        case CMD_START_SEQ:
            prepare(args[0] & 0xf, args[1], args[2], args[3]);
            set_flag(player_at(args[0]), PF_PREPARED, 1);
            break;
        case CMD_PREPARE_SEQ:
            prepare(args[0] & 0xf, args[1], args[2], args[3]);
            break;
        case CMD_START_PREPARED_SEQ:
            set_flag(player_at(args[0]), PF_PREPARED, 1);
            break;
        case CMD_STOP_SEQ:
            if (has(player_at(args[0]), PF_ACTIVE)) {
                player_stop(player_at(args[0]));
                status_bit(args[0] & 0xf, 0);
            }
            break;
        case CMD_PAUSE_SEQ:
            set_flag(player_at(args[0]), PF_PAUSE, args[1] & 1);
            break;
        case CMD_SKIP_SEQ: { /* (0x6e04) the alarm stopped and started again after the skip */
            uint32_t p = player_at(args[0]), done = 0;
            for (; done < args[1]; done++) {
                if (player_tick(p, 0)) {
                    player_stop(p);
                    break;
                }
            }
            sq.next_period = io_cycles() + FIRST_DELAY_CYCLES;
            add_ticks(p, done);
            break;
        }
        case CMD_PLAYER_PARAM:
            set_sized(player_at(args[0]) + args[1], args[2], args[3]);
            break;
        case CMD_TRACK_PARAM: {
            uint32_t p = player_at(args[0] & 0xffffff), mask = args[1];
            for (uint32_t i = 0; i < TRACKS_PER_PLAYER && mask != 0; i++, mask >>= 1) {
                uint32_t t = (mask & 1) ? player_track(p, i) : 0;
                if (t != 0) {
                    set_sized(t + args[2], args[3], args[0] >> 24);
                }
            }
            break;
        }
        case CMD_MUTE_TRACK: {
            uint32_t p = player_at(args[0]), mask = args[1];
            for (uint32_t i = 0; i < TRACKS_PER_PLAYER && mask != 0; i++, mask >>= 1) {
                uint32_t t = (mask & 1) ? player_track(p, i) : 0;
                if (t != 0) {
                    set_flag(t, TF_MUTE, args[2] & 1);
                }
            }
            break;
        }
        case CMD_ALLOCATABLE_CHANNEL: {
            uint32_t p = player_at(args[0]), mask = args[1];
            for (uint32_t i = 0; i < TRACKS_PER_PLAYER && mask != 0; i++, mask >>= 1) {
                uint32_t t = (mask & 1) ? player_track(p, i) : 0;
                if (t != 0) {
                    set16(t + T_CHANNEL_MASK, args[2]);
                    set_flag(t, TF_CHANNEL_MASK, 1);
                }
            }
            break;
        }
        case CMD_PLAYER_LOCAL_VAR:
            if (shared_work != 0) {
                guest_store16(shared_work + SW_PLAYER + (args[0] & 0xf) * PLAYER_SIZE + args[1] * 2, args[2]);
            }
            break;
        case CMD_PLAYER_GLOBAL_VAR:
            if (shared_work != 0) {
                guest_store16(shared_work + SW_GLOBAL + args[0] * 2, args[1]);
            }
            break;
        case CMD_LOCK_CHANNEL:
            if (args[1] & 1) {
                sq.locked_weak |= args[0];
            } else {
                sq.locked |= args[0];
            }
            break;
        case CMD_UNLOCK_CHANNEL:
            if (args[1] & 1) {
                sq.locked_weak &= ~args[0];
            } else {
                sq.locked &= ~args[0];
            }
            break;
        case CMD_INVALIDATE_SEQ: /* (0x6c54) a player stopped when a track reads in the range */
            for (uint32_t no = 0; no < PLAYERS; no++) {
                uint32_t p = player_at(no);
                if (!has(p, PF_ACTIVE)) {
                    continue;
                }
                for (uint32_t i = 0; i < TRACKS_PER_PLAYER; i++) {
                    uint32_t t = player_track(p, i);
                    if (t != 0 && args[0] <= w32(t + T_CUR) && w32(t + T_CUR) <= args[1]) {
                        player_stop(p);
                        break;
                    }
                }
            }
            break;
        case CMD_INVALIDATE_BANK: /* (0x6bf4) a player stopped when its bank is in the range */
            for (uint32_t no = 0; no < PLAYERS; no++) {
                uint32_t p = player_at(no);
                if (has(p, PF_ACTIVE) && args[0] <= w32(p + P_BANK) && w32(p + P_BANK) <= args[1]) {
                    player_stop(p);
                }
            }
            break;
        case CMD_READ_DRIVER_INFO:
            read_driver_info(args[0]);
            break;
        default: /* the channels, the timers, capture, alarms, volumes: nothing sounds */
            break;
    }
}

void sequencer_after_list(uint32_t shared_work)
{
    sq.shared_work = shared_work;
    thread_pass(0);
}

void sequencer_advance(uint32_t shared_work)
{
    sq.shared_work = shared_work;
    while (io_cycles() >= sq.next_period) {
        sq.next_period += PERIOD_CYCLES;
        sq.periods++;
        thread_pass(1);
    }
}

void sequencer_report(FILE *out)
{
    if (!sq.on) {
        return;
    }
    uint32_t active = 0;
    for (uint32_t no = 0; no < PLAYERS; no++) {
        active |= has(player_at(no), PF_ACTIVE) ? 1u << no : 0;
    }
    fprintf(out,
            "sequencer: %llu periodic passes, %llu commands, %llu sequences started, %llu ended, %llu ticks; "
            "players active %04x\n",
            (unsigned long long) sq.periods, (unsigned long long) sq.commands, (unsigned long long) sq.started,
            (unsigned long long) sq.finished, (unsigned long long) sq.ticks, (unsigned) active);
}
