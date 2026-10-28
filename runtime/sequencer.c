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
 * The channels: a note takes one of the 16 by the driver's rules (the instrument from the
 * player's bank, SBNK, the channels its kind may use, the priorities, the channels the ARM9
 * locked), and keeps it until it ends: by its envelope (attack, decay, sustain, then release
 * from the note's end to -72.3 dB), or when its sample, played once, has played out. The
 * envelope, the modulation and the sweep are run as the driver runs them (0x50b0), so the
 * volume and the pitch, which decide those ends, are the driver's. The hardware's channels are
 * kept only as far as the driver reads them back: their control register, and whether each
 * still plays (a sample played once stops after its length at the rate its timer gives).
 * Nothing is mixed and no sound is made.
 *
 * Two tables the driver uses are in the ARM7's BIOS, not in the ROM. The volume table
 * (SVC_GetVolumeTable: a level in 0.1 dB as a register volume for its divider) is read from the
 * ARM9's copy of it (VolumeTable, 0x0213d70c in autoload_2, which the ARM9's
 * SND_CalcChannelVolume reads in its place). The pitch table (SVC_GetPitchTable: 2^(i/768) - 1
 * as a 16-bit fraction) has no copy in the ROM; it is computed from that definition, in
 * integers so that every host gets the same numbers, and an entry can differ from the BIOS's by
 * its rounding. It only sets how long a sample played once lasts, so such a sample's end can
 * fall a periodic pass from the hardware's. The driver's own tables (decibels, sine, attack,
 * channel order) are read from the ARM7 binary in the ROM. */
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

/* SNDExChannel */
#define C_TYPE 0x01       /* 0 a sample, 1 a square wave (PSG), 2 noise */
#define C_ENV_STATUS 0x02 /* 0 attack, 1 decay, 2 sustain, 3 release */
#define C_FLAGS 0x03      /* bits 0-2 the flags below; 3-7 what the next pass writes (SYNC_) */
#define C_PAN_RANGE 0x04
#define C_ORIGINAL_KEY 0x05
#define C_USER_DECAY2 0x06
#define C_KEY 0x08
#define C_VELOCITY 0x09
#define C_INIT_PAN 0x0a
#define C_USER_PAN 0x0b
#define C_USER_DECAY 0x0c
#define C_USER_PITCH 0x0e
#define C_ENVELOPE 0x10 /* the envelope's level, in 1/128 of 0.1 dB */
#define C_SWEEP_COUNTER 0x14
#define C_SWEEP_LENGTH 0x18
#define C_ATTACK 0x1c
#define C_SUSTAIN 0x1d
#define C_DECAY 0x1e
#define C_RELEASE 0x20
#define C_PRIO 0x22
#define C_PAN 0x23
#define C_VOLUME 0x24 /* the register's volume and divider (bits 8-9) */
#define C_TIMER 0x26
#define C_LFO 0x28 /* target, speed, depth, range, delay; then the delay's count and the phase */
#define C_LFO_TARGET 0x28
#define C_LFO_SPEED 0x29
#define C_LFO_DEPTH 0x2a
#define C_LFO_RANGE 0x2b
#define C_LFO_DELAY 0x2c
#define C_LFO_DELAY_COUNTER 0x2e
#define C_LFO_COUNTER 0x30
#define C_SWEEP_PITCH 0x32
#define C_LENGTH 0x34
#define C_WAVE 0x38 /* SNDWaveParam: format, loop, rate, timer, loop start, loop length */
#define C_WAVE_FORMAT 0x38
#define C_WAVE_LOOP 0x39
#define C_WAVE_TIMER 0x3c
#define C_WAVE_LOOP_START 0x3e
#define C_WAVE_LOOP_LENGTH 0x40
#define C_DATA 0x44 /* the sample's address, or a square wave's duty */
#define C_CALLBACK 0x48
#define C_CALLBACK_DATA 0x4c
#define C_NEXT 0x50
#define CF_ACTIVE 0x01u
#define CF_START 0x02u
#define CF_AUTO_SWEEP 0x04u
#define SYNC_START 0x01u
#define SYNC_STOP 0x02u
#define SYNC_TIMER 0x04u
#define SYNC_VOLUME 0x08u
#define SYNC_PAN 0x10u
/* The only callback a channel is given here, the track's (0x6454), at its ARM7 address. */
#define TRACK_CALLBACK 0x037fe1c8u
#define CALLBACK_DROP 0   /* another note took the channel */
#define CALLBACK_FINISH 1 /* the channel ended */
#define DECIBEL_MIN (-723)
#define ENVELOPE_START (DECIBEL_MIN * 128)
#define CHANNEL_MASK_SAMPLE 0xffffu /* 0x6148 */
#define CHANNEL_MASK_PSG 0x3f00u
#define CHANNEL_MASK_NOISE 0xc000u
#define WAVE_TIMER_PSG 0x1f46u /* the base timer of a square wave and of noise (0x5000, 0x4fd4) */

/* Instrument kinds in a bank (0x73fc): one note's data, a drum set by key, a key split. */
enum {
    INST_PCM = 1,
    INST_PSG = 2,
    INST_NOISE = 3,
    INST_DIRECT_PCM = 4,
    INST_NULL = 5,
    INST_DRUM_SET = 0x10,
    INST_KEY_SPLIT = 0x11
};

/* The driver's tables in the ARM7 binary, by their ARM7 address. The binary's part from offset
 * 0x28c is the driver's code and data, which the ARM7's start-up copies to 0x037f8000. */
#define ARM7_WRAM_DELTA 0x037f7d74u
#define TABLE_SINE 0x03806f1cu    /* 33 signed bytes: a quarter of a sine wave, 127 at the top */
#define TABLE_DECIBEL 0x03806f40u /* 128 signed halfwords: a volume 0-127 in 0.1 dB */
#define TABLE_SHIFT 0x03807040u   /* the register divider's shifts: 0, 1, 2, 4 */
#define TABLE_ORDER 0x03807044u   /* the channels in the order a new note looks at them */
#define TABLE_ATTACK 0x03807054u  /* the attack rates of 0x6d-0x7f */
#define PITCH_TABLE_SIZE 768
#define VOLUME_TABLE 0x0213d70cu /* the ARM9's copy of the BIOS's volume table, 724 bytes */

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
    CMD_STOP_UNLOCKED_CHANNEL = 0x1c,
    CMD_INVALIDATE_SEQ = 0x1e,
    CMD_INVALIDATE_BANK = 0x1f,
    CMD_INVALIDATE_WAVE = 0x20,
    CMD_READ_DRIVER_INFO = 0x21,
};

/* A hardware channel, as far as the driver reads it back: its control register (bit 31 while
 * it plays) and, for a sample played once, how far it has played. */
typedef struct HwChannel {
    uint32_t control;
    uint32_t timer;  /* the timer register: the sample period is 0x10000 - timer at 16.76 MHz */
    uint32_t start;  /* the loop start, in words */
    uint32_t length; /* the loop length, in words */
    uint64_t last;   /* the bus cycle the position is counted to */
    uint64_t played; /* samples played, and the bus cycles towards the next */
    uint64_t part;
} HwChannel;

static struct {
    int on;
    uint8_t work[WORK_SIZE];
    uint32_t random; /* the driver's random number state (0x41fc), 0x12345678 at the start */
    uint64_t next_period;
    uint32_t locked, locked_weak; /* the channels locked by the ARM9 (strong, weak) */
    uint32_t shared_work;         /* as the command being run sees it */
    uint64_t now;                 /* the bus cycle of the pass being run */
    HwChannel hw[CHANNELS];
    uint8_t *driver; /* the driver's code and data, as the ARM7 has them from 0x037f8000 */
    uint32_t driver_size;
    uint16_t pitch[PITCH_TABLE_SIZE];
    uint64_t periods, ticks, started, finished, commands, notes, no_channel, channels_ended;
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

static int32_t ws8(uint32_t o)
{
    return (int8_t) w8(o);
}

static int32_t ws16(uint32_t o)
{
    return (int16_t) w16(o);
}

static int32_t ws32(uint32_t o)
{
    return (int32_t) w32(o);
}

/* The work's offset of a pointer the driver keeps (an ARM7 address into the work), and back. */
static uint32_t work_offset(uint32_t address)
{
    return address - WORK_ADDRESS;
}

static uint32_t work_address(uint32_t o)
{
    return WORK_ADDRESS + o;
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

static uint32_t guest32(uint32_t a)
{
    uint32_t v = 0;
    bus_read(a, 4, &v);
    return v;
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

/* --- the hardware's channels --- */

#define HW_BUSY 0x80000000u
#define HW_FORMAT(control) (((control) >> 29) & 3) /* 0 PCM8, 1 PCM16, 2 ADPCM, 3 PSG/noise */
#define HW_REPEAT(control) (((control) >> 27) & 3) /* 1 a loop, 2 played once */

/* The samples a sample played once has, from the loop start and length (words). */
static uint64_t hw_samples(const HwChannel *h)
{
    uint64_t words = (uint64_t) h->start + h->length;
    switch (HW_FORMAT(h->control)) {
        case 0:
            return words * 4;
        case 1:
            return words * 2;
        default: /* ADPCM: the first word is its header */
            return words != 0 ? (words - 1) * 8 : 0;
    }
}

/* The channel's position counted up to the pass's time: a sample played once stops at its end.
 * The timer counts at half the bus clock. */
static void hw_advance(uint32_t no)
{
    HwChannel *h = &sq.hw[no];
    if ((h->control & HW_BUSY) && HW_FORMAT(h->control) != 3 && HW_REPEAT(h->control) == 2 && sq.now > h->last) {
        uint64_t period = 2 * (uint64_t) (0x10000u - (h->timer & 0xffff));
        uint64_t elapsed = sq.now - h->last + h->part;
        h->played += elapsed / period;
        h->part = elapsed % period;
        if (h->played >= hw_samples(h)) {
            h->control &= ~HW_BUSY;
        }
    }
    if (sq.now > h->last) {
        h->last = sq.now;
    }
}

/* Whether the channel plays (0x3e64). */
static int hw_busy(uint32_t no)
{
    hw_advance(no);
    return (sq.hw[no].control & HW_BUSY) != 0;
}

/* The channel stopped, `hold` keeping its last sample (0x3f98). */
static void hw_stop(uint32_t no, int hold)
{
    hw_advance(no);
    sq.hw[no].control = (sq.hw[no].control & ~HW_BUSY) | (hold ? 0x8000u : 0);
}

/* The control register written whole (0x412c, 0x4074, 0x3fc4); it does not start the channel. */
static void hw_setup(uint32_t no, uint32_t control, uint32_t timer, uint32_t start, uint32_t length)
{
    HwChannel *h = &sq.hw[no];
    hw_advance(no);
    h->control = control & ~HW_BUSY;
    h->timer = (0x10000u - timer) & 0xffff;
    h->start = start & 0xffff;
    h->length = length & 0x3fffff;
}

static void hw_set_timer(uint32_t no, uint32_t timer)
{
    hw_advance(no);
    sq.hw[no].timer = (0x10000u - timer) & 0xffff;
}

/* The volume and divider (0x3f14) and the pan (0x3e80); the master pan and the output effect,
 * which the driver applies here when the ARM9 sets them, are left out. */
static void hw_set_volume(uint32_t no, uint32_t volume, uint32_t divider)
{
    sq.hw[no].control = (sq.hw[no].control & ~0xffffu) | (volume & 0xff) | (divider & 0xff) << 8;
}

static void hw_set_pan(uint32_t no, uint32_t pan)
{
    sq.hw[no].control = (sq.hw[no].control & ~0xff0000u) | (pan & 0xff) << 16;
}

static void hw_start(uint32_t no)
{
    HwChannel *h = &sq.hw[no];
    hw_advance(no);
    if (!(h->control & HW_BUSY)) {
        h->played = 0;
        h->part = 0;
        h->last = sq.now;
    }
    h->control |= HW_BUSY;
}

/* --- the driver's tables --- */

/* A byte of the driver's memory at an ARM7 address (its tables are read where the driver reads
 * them, past their ends too where a setting takes it there); 0 outside it. */
static uint32_t driver8(uint32_t address)
{
    uint32_t o = address - ARM7_WRAM_DELTA;
    return o >= 0x28cu && o < sq.driver_size ? sq.driver[o] : 0;
}

/* A volume of 0-255 in 0.1 dB (the halfword table at TABLE_DECIBEL). */
static int32_t decibel(uint32_t volume)
{
    uint32_t a = TABLE_DECIBEL + 2 * (volume & 0xff);
    return (int16_t) (driver8(a) | driver8(a + 1) << 8);
}

/* --- the BIOS's tables (see the top of the file) --- */

/* x * y in 2.30 fixed point, rounded. */
static uint64_t mul30(uint64_t x, uint64_t y)
{
    return (x * y + (1ull << 29)) >> 30;
}

/* The pitch table: 2^(i/768) - 1 in 16-bit fraction, rounded. */
static void pitch_table(void)
{
    const uint64_t step = 1082278220ull; /* 2^(1/768) in 2.30 */
    uint64_t x = 1ull << 30;
    for (int i = 0; i < PITCH_TABLE_SIZE; i++) {
        sq.pitch[i] = (uint16_t) ((((x - (1ull << 30)) << 16) + (1ull << 29)) >> 30);
        x = mul30(x, step);
    }
}

/* The register volume with its divider for a level in 0.1 dB (0x429c). */
static uint32_t channel_volume(int32_t db)
{
    db = db < DECIBEL_MIN ? DECIBEL_MIN : db > 0 ? 0 : db;
    uint32_t divider = db < -240 ? 3 : db < -120 ? 2 : db < -60 ? 1 : 0;
    return (guest8(VOLUME_TABLE + (uint32_t) (db - DECIBEL_MIN)) | divider << 8) & 0xffff;
}

/* The timer for a base timer and a pitch in 1/64 semitones (0x4320, SND_CalcTimer). */
static uint32_t channel_timer(uint32_t base, int32_t pitch)
{
    int32_t octave = 0, n = -pitch;
    while (n < 0) {
        octave--;
        n += PITCH_TABLE_SIZE;
    }
    while (n >= PITCH_TABLE_SIZE) {
        octave++;
        n -= PITCH_TABLE_SIZE;
    }
    uint64_t t = ((uint64_t) sq.pitch[n] + 0x10000) * (uint64_t) (int64_t) (int32_t) base;
    int32_t shift = octave - 16;
    if (shift <= 0) {
        t >>= -shift;
    } else if (shift < 32) {
        if (t & ~(~0ull >> shift)) {
            return 0xffff;
        }
        t <<= shift;
    } else {
        return 0xffff;
    }
    return t < 0x10 ? 0x10 : t > 0xffff ? 0xffff : (uint32_t) t;
}

/* --- the driver's channels --- */

static uint32_t channel_at(uint32_t no)
{
    return (no & 0xf) * CHANNEL_SIZE;
}

static uint32_t channel_no(uint32_t c)
{
    return w8(c);
}

static uint32_t sync_flags(uint32_t c)
{
    return w8(c + C_FLAGS) >> 3;
}

static void set_sync(uint32_t c, uint32_t flags)
{
    set8(c + C_FLAGS, (w8(c + C_FLAGS) & 7) | (flags & 0x1f) << 3);
}

static void add_sync(uint32_t c, uint32_t flags)
{
    set_sync(c, sync_flags(c) | flags);
}

static void channel_clear_callback(uint32_t c) /* 0x4d54 */
{
    set32(c + C_CALLBACK, 0);
    set32(c + C_CALLBACK_DATA, 0);
}

static void set_attack(uint32_t c, uint32_t attack) /* 0x4efc */
{
    attack &= 0xff;
    set8(c + C_ATTACK, attack < 0x6d ? 0xff - attack : driver8(TABLE_ATTACK + 0x7f - attack));
}

/* A decay or release rate from its 0-127 setting (0x4968). */
static uint32_t envelope_rate(uint32_t v)
{
    v &= 0xff;
    if (v == 0x7f) {
        return 0xffff;
    }
    if (v == 0x7e) {
        return 0x3c00;
    }
    if (v < 0x32) {
        return ((v << 1) + 1) & 0xffff;
    }
    return (uint32_t) (0x1e00 / (0x7e - (int32_t) v)) & 0xffff; /* (a signed division) */
}

static void set_decay(uint32_t c, uint32_t v)
{
    set16(c + C_DECAY, envelope_rate(v));
}

static void set_sustain(uint32_t c, uint32_t v)
{
    set8(c + C_SUSTAIN, v);
}

static void set_release(uint32_t c, uint32_t v)
{
    set16(c + C_RELEASE, envelope_rate(v));
}

/* The modulation's settings (0x4a8c) and its start (0x4a7c). */
static void lfo_init(uint32_t c)
{
    set8(c + C_LFO_TARGET, 0);
    set8(c + C_LFO_DEPTH, 0);
    set8(c + C_LFO_RANGE, 1);
    set8(c + C_LFO_SPEED, 0x10);
    set16(c + C_LFO_DELAY, 0);
}

static void lfo_start(uint32_t c)
{
    set16(c + C_LFO_COUNTER, 0);
    set16(c + C_LFO_DELAY_COUNTER, 0);
}

/* A channel given to a note (0x48bc): its callback, priority and defaults. */
static void channel_init(uint32_t c, uint32_t callback, uint32_t data, uint32_t prio)
{
    set32(c + C_NEXT, 0);
    set32(c + C_CALLBACK, callback);
    set32(c + C_CALLBACK_DATA, data);
    set32(c + C_LENGTH, 0);
    set8(c + C_PRIO, prio);
    set16(c + C_VOLUME, 0x7f);
    set_flag(c + C_FLAGS, CF_START, 0);
    set_flag(c + C_FLAGS, CF_AUTO_SWEEP, 1);
    set8(c + C_KEY, 60);
    set8(c + C_ORIGINAL_KEY, 60);
    set8(c + C_VELOCITY, 0x7f);
    set8(c + C_INIT_PAN, 0);
    set16(c + C_USER_DECAY, 0);
    set16(c + C_USER_DECAY2, 0);
    set16(c + C_USER_PITCH, 0);
    set8(c + C_USER_PAN, 0);
    set8(c + C_PAN_RANGE, 0x7f);
    set16(c + C_SWEEP_PITCH, 0);
    set32(c + C_SWEEP_LENGTH, 0);
    set32(c + C_SWEEP_COUNTER, 0);
    set_attack(c, 0x7f);
    set_decay(c, 0x7f);
    set_sustain(c, 0x7f);
    set_release(c, 0x7f);
    lfo_init(c);
}

/* The channel started for `length` ticks, or -1 for as long as it sounds (0x4870). */
static void channel_start(uint32_t c, int32_t length)
{
    set32(c + C_ENVELOPE, (uint32_t) ENVELOPE_START);
    set8(c + C_ENV_STATUS, 0);
    set32(c + C_LENGTH, (uint32_t) length);
    lfo_start(c);
    set_flag(c + C_FLAGS, CF_START, 1);
    set_flag(c + C_FLAGS, CF_ACTIVE, 1);
}

/* A sample's channel (0x5074): its parameters (12 bytes from `wave`) and data after them. */
static void channel_start_pcm(uint32_t c, uint32_t wave, int32_t length)
{
    set8(c + C_TYPE, 0);
    for (uint32_t i = 0; i < 12; i++) {
        set8(c + C_WAVE + i, guest8(wave + i));
    }
    set32(c + C_DATA, wave + 12);
    channel_start(c, length);
}

/* A square wave on channels 8-13 (0x5020) and noise on 14 and 15 (0x4fd4). */
static int channel_start_psg(uint32_t c, uint32_t duty, int32_t length)
{
    if (channel_no(c) < 8 || channel_no(c) > 13) {
        return 0;
    }
    set8(c + C_TYPE, 1);
    set32(c + C_DATA, duty);
    set16(c + C_WAVE_TIMER, WAVE_TIMER_PSG);
    channel_start(c, length);
    return 1;
}

static int channel_start_noise(uint32_t c, int32_t length)
{
    if (channel_no(c) < 14) {
        return 0;
    }
    set8(c + C_TYPE, 2);
    set16(c + C_WAVE_TIMER, WAVE_TIMER_PSG);
    channel_start(c, length);
    return 1;
}

/* The track's callback (0x6454): the channel taken out of the track's list; when it ended, its
 * priority and callback cleared too. */
static void track_channel_callback(uint32_t c, int status, uint32_t track)
{
    uint32_t t = work_offset(track), me = work_address(c);
    if (status == CALLBACK_FINISH) {
        set8(c + C_PRIO, 0);
        channel_clear_callback(c);
    }
    if (w32(t + T_CHANNELS) == me) {
        set32(t + T_CHANNELS, w32(c + C_NEXT));
        return;
    }
    for (uint32_t a = w32(t + T_CHANNELS); a != 0;) {
        uint32_t o = work_offset(a);
        if (w32(o + C_NEXT) == me) {
            set32(o + C_NEXT, w32(c + C_NEXT));
            return;
        }
        a = w32(o + C_NEXT);
    }
}

/* The channel's callback called, when it has one; 0 when it has none. */
static int channel_callback(uint32_t c, int status)
{
    if (w32(c + C_CALLBACK) != TRACK_CALLBACK) {
        return 0;
    }
    track_channel_callback(c, status, w32(c + C_CALLBACK_DATA));
    return 1;
}

/* Which of two channels is quieter by their registers' volume (0x4810): 1 when `a` is, -1 when
 * `b` is, 0 when they are as loud. */
static int channel_compare(uint32_t a, uint32_t b)
{
    uint32_t va = w16(a + C_VOLUME), vb = w16(b + C_VOLUME);
    int32_t la = (int32_t) ((va & 0xff) << 4) >> (driver8(TABLE_SHIFT + (va >> 8)) & 31);
    int32_t lb = (int32_t) ((vb & 0xff) << 4) >> (driver8(TABLE_SHIFT + (vb >> 8)) & 31);
    return la == lb ? 0 : la < lb ? 1 : -1;
}

/* A channel for a note (0x4d68): of those in `mask` the ARM9 has not locked, in the driver's
 * order, the one of the lowest priority (of equal ones the quieter), if it is not above `prio`.
 * Its note, if it had one, is told it lost it. 0 when there is none. */
static uint32_t channel_alloc(uint32_t mask, int32_t prio, int strong, uint32_t callback, uint32_t data)
{
    mask &= ~sq.locked;
    if (!strong) {
        mask &= ~sq.locked_weak;
    }
    uint32_t best = 0;
    int found = 0;
    for (uint32_t i = 0; i < CHANNELS; i++) {
        uint32_t no = driver8(TABLE_ORDER + i) & 0xf;
        if (!(mask & 1u << no)) {
            continue;
        }
        uint32_t c = channel_at(no);
        if (!found) {
            best = c;
            found = 1;
            continue;
        }
        if (w8(c + C_PRIO) > w8(best + C_PRIO)) {
            continue;
        }
        if (w8(c + C_PRIO) == w8(best + C_PRIO) && channel_compare(best, c) >= 0) {
            continue;
        }
        best = c;
    }
    if (!found || prio < (int32_t) w8(best + C_PRIO)) {
        return UINT32_MAX;
    }
    channel_callback(best, CALLBACK_DROP);
    set_sync(best, SYNC_STOP);
    set_flag(best + C_FLAGS, CF_ACTIVE, 0);
    channel_init(best, callback, data, (uint32_t) prio);
    return best;
}

/* The channels in `mask` not locked already lose their notes and stop (0x4b94, 0x4c8c). */
static void channel_drop(uint32_t mask)
{
    for (uint32_t no = 0; no < CHANNELS && (mask >> no) != 0; no++) {
        if (!(mask & 1u << no) || (sq.locked & 1u << no)) {
            continue;
        }
        uint32_t c = channel_at(no);
        channel_callback(c, CALLBACK_DROP);
        hw_stop(no, 0);
        set8(c + C_PRIO, 0);
        channel_clear_callback(c);
        set_sync(c, 0);
        set_flag(c + C_FLAGS, CF_ACTIVE, 0);
    }
}

/* The ARM9's lock of channels (0x4b94). */
static void channel_lock(uint32_t mask, int weak)
{
    channel_drop(mask);
    if (weak) {
        sq.locked_weak |= mask;
    } else {
        sq.locked |= mask;
    }
}

/* The sample data from `from` to `to` going away (0x4ab0): the channels playing it stop. */
static void channel_invalidate_wave(uint32_t from, uint32_t to)
{
    for (uint32_t no = 0; no < CHANNELS; no++) {
        uint32_t c = channel_at(no);
        if (has(c + C_FLAGS, CF_ACTIVE) && w8(c + C_TYPE) == 0 && from <= w32(c + C_DATA) && w32(c + C_DATA) <= to) {
            set_flag(c + C_FLAGS, CF_START, 0);
            hw_stop(no, 0);
        }
    }
}

/* The envelope's step (0x4f20), when `update`; its level in 0.1 dB. */
static int32_t channel_envelope(uint32_t c, int update)
{
    if (update) {
        int32_t level = ws32(c + C_ENVELOPE);
        switch (w8(c + C_ENV_STATUS)) {
            case 0:
                level = -((-level * (int32_t) w8(c + C_ATTACK)) >> 8);
                set32(c + C_ENVELOPE, (uint32_t) level);
                if (level == 0) {
                    set8(c + C_ENV_STATUS, 1);
                }
                break;
            case 1: {
                int32_t sustain = decibel(w8(c + C_SUSTAIN)) << 7;
                level -= (int32_t) w16(c + C_DECAY);
                set32(c + C_ENVELOPE, (uint32_t) level);
                if (level <= sustain) {
                    set32(c + C_ENVELOPE, (uint32_t) sustain);
                    set8(c + C_ENV_STATUS, 2);
                }
                break;
            }
            case 3:
                set32(c + C_ENVELOPE, (uint32_t) (level - (int32_t) w16(c + C_RELEASE)));
                break;
            default:
                break;
        }
    }
    return ws32(c + C_ENVELOPE) >> 7;
}

/* The sweep's pitch now (0x47a0), its counter stepped when `update` and the sweep is timed by
 * the passes. */
static int32_t channel_sweep(uint32_t c, int update)
{
    int32_t pitch = ws16(c + C_SWEEP_PITCH), counter = ws32(c + C_SWEEP_COUNTER), length = ws32(c + C_SWEEP_LENGTH);
    if (pitch == 0 || counter >= length) {
        return 0;
    }
    int32_t v = (int32_t) ((int64_t) pitch * (int64_t) (length - counter) / length);
    if (update && has(c + C_FLAGS, CF_AUTO_SWEEP)) {
        set32(c + C_SWEEP_COUNTER, (uint32_t) (counter + 1));
    }
    return v;
}

/* The sine of a phase of 0-127 (0x4230). */
static int32_t sine(uint32_t i)
{
    return (int8_t) driver8(TABLE_SINE + i);
}

static int32_t lfo_sine(uint32_t x)
{
    if (x < 0x20) {
        return sine(x);
    }
    if (x < 0x40) {
        return sine(0x40 - x);
    }
    if (x < 0x60) {
        return (int8_t) -sine(x - 0x40);
    }
    return (int8_t) -sine(0x20 - (x - 0x60));
}

/* The modulation's value (0x4704 with 0x49c8), its phase stepped when `update` (0x4a18). */
static int32_t channel_lfo(uint32_t c, int update)
{
    int64_t v = 0;
    if (w8(c + C_LFO_DEPTH) != 0 && w16(c + C_LFO_DELAY_COUNTER) >= w16(c + C_LFO_DELAY)) {
        v = (int64_t) lfo_sine(w16(c + C_LFO_COUNTER) >> 8) * w8(c + C_LFO_DEPTH) * w8(c + C_LFO_RANGE);
    }
    if (v != 0) {
        switch (w8(c + C_LFO_TARGET)) {
            case 0: /* the pitch */
            case 2: /* the pan */
                v *= 64;
                break;
            case 1: /* the volume */
                v *= 60;
                break;
            default:
                break;
        }
    }
    int32_t result = (int32_t) (uint32_t) ((uint64_t) v >> 14);
    if (update) {
        if (w16(c + C_LFO_DELAY_COUNTER) < w16(c + C_LFO_DELAY)) {
            set16(c + C_LFO_DELAY_COUNTER, w16(c + C_LFO_DELAY_COUNTER) + 1);
        } else {
            uint32_t counter = w16(c + C_LFO_COUNTER), step = w8(c + C_LFO_SPEED) << 6;
            uint32_t phase = (counter + step) >> 8;
            while (phase >= 0x80) {
                phase -= 0x80;
            }
            counter = ((counter + step) & 0xff) | phase << 8;
            set16(c + C_LFO_COUNTER, counter);
        }
    }
    return result;
}

/* A channel ended: its note told, its volume 0, inactive (0x5158, 0x5264). */
static void channel_finish(uint32_t c)
{
    if (!channel_callback(c, CALLBACK_FINISH)) {
        set8(c + C_PRIO, 0);
    }
    set16(c + C_VOLUME, 0);
    set_flag(c + C_FLAGS, CF_ACTIVE, 0);
    sq.channels_ended++;
}

/* The channels' pass (0x50b0): a channel whose hardware stopped ends; the others' volume, pitch
 * and pan worked out (the envelope, sweep and modulation stepped on a periodic pass), and a
 * released one ends once it is down to -72.3 dB. What changed is written on the next pass. */
static void channel_main(int update)
{
    for (uint32_t no = 0; no < CHANNELS; no++) {
        uint32_t c = channel_at(no);
        if (!has(c + C_FLAGS, CF_ACTIVE)) {
            continue;
        }
        if (has(c + C_FLAGS, CF_START)) {
            add_sync(c, SYNC_START);
            set_flag(c + C_FLAGS, CF_START, 0);
        } else if (!hw_busy(no)) {
            channel_finish(c);
            continue;
        }
        int32_t volume = decibel(w8(c + C_VELOCITY));
        int32_t pitch = ((int32_t) w8(c + C_KEY) - (int32_t) w8(c + C_ORIGINAL_KEY)) * 64;
        int32_t pan = 0;
        volume += channel_envelope(c, update);
        pitch += channel_sweep(c, update);
        int32_t lfo = channel_lfo(c, update);
        switch (w8(c + C_LFO_TARGET)) {
            case 0:
                pitch += lfo;
                break;
            case 1:
                volume += lfo;
                break;
            case 2:
                pan += lfo;
                break;
            default:
                break;
        }
        pan += ws8(c + C_INIT_PAN);
        if (w8(c + C_PAN_RANGE) != 0x7f) {
            pan = (pan * (int32_t) w8(c + C_PAN_RANGE) + 0x40) >> 7;
        }
        volume += ws16(c + C_USER_DECAY) + ws16(c + C_USER_DECAY2);
        pitch += ws16(c + C_USER_PITCH);
        pan += ws8(c + C_USER_PAN);
        if (w8(c + C_ENV_STATUS) == 3 && volume <= DECIBEL_MIN) {
            set_sync(c, SYNC_STOP);
            channel_finish(c);
            continue;
        }
        uint32_t reg_volume = channel_volume(volume);
        uint32_t timer = channel_timer(w16(c + C_WAVE_TIMER), pitch);
        if (w8(c + C_TYPE) == 1) {
            timer &= 0xfffc;
        }
        pan += 0x40;
        pan = pan < 0 ? 0 : pan > 0x7f ? 0x7f : pan;
        if (reg_volume != w16(c + C_VOLUME)) {
            set16(c + C_VOLUME, reg_volume);
            add_sync(c, SYNC_VOLUME);
        }
        if (timer != w16(c + C_TIMER)) {
            set16(c + C_TIMER, timer);
            add_sync(c, SYNC_TIMER);
        }
        if ((uint32_t) pan != w8(c + C_PAN)) {
            set8(c + C_PAN, (uint32_t) pan);
            add_sync(c, SYNC_PAN);
        }
    }
}

/* What the last channels' pass decided written to the hardware (0x53bc): channels stopped,
 * set up and started, or their timer, volume and pan changed. */
static void channel_sync(void)
{
    for (uint32_t no = 0; no < CHANNELS; no++) {
        uint32_t c = channel_at(no), flags = sync_flags(c);
        if (flags == 0) {
            continue;
        }
        if (flags & SYNC_STOP) {
            hw_stop(no, 0);
        }
        uint32_t volume = w16(c + C_VOLUME), base = (volume & 0xff) | (volume >> 8 & 0xff) << 8 | w8(c + C_PAN) << 16;
        if (flags & SYNC_START) {
            switch (w8(c + C_TYPE)) {
                case 0: {
                    uint32_t repeat = w8(c + C_WAVE_LOOP) != 0 ? 1 : 2;
                    hw_setup(no, base | repeat << 27 | (w8(c + C_WAVE_FORMAT) & 3) << 29, w16(c + C_TIMER),
                             w16(c + C_WAVE_LOOP_START), w32(c + C_WAVE_LOOP_LENGTH));
                    break;
                }
                case 1:
                    hw_setup(no, base | w32(c + C_DATA) << 24 | 0x60000000u, w16(c + C_TIMER), 0, 0);
                    break;
                case 2:
                    hw_setup(no, base | 0x60000000u, w16(c + C_TIMER), 0, 0);
                    break;
                default:
                    break;
            }
        } else {
            if (flags & SYNC_TIMER) {
                hw_set_timer(no, w16(c + C_TIMER));
            }
            if (flags & SYNC_VOLUME) {
                hw_set_volume(no, volume & 0xff, volume >> 8);
            }
            if (flags & SYNC_PAN) {
                hw_set_pan(no, w8(c + C_PAN));
            }
        }
    }
    for (uint32_t no = 0; no < CHANNELS; no++) {
        uint32_t c = channel_at(no);
        if (sync_flags(c) == 0) {
            continue;
        }
        if (sync_flags(c) & SYNC_START) {
            hw_start(no);
        }
        set_sync(c, 0);
    }
}

/* --- notes --- */

/* The instrument for `prg` and `key` in the bank at `bank` (0x73fc), as 12 bytes: its kind,
 * then (from 2) the wave, the wave archive, the original key, attack, decay, sustain, release and
 * pan. 0 when there is none. */
static int bank_instrument(uint32_t bank, uint32_t prg, uint32_t key, uint8_t out[12])
{
    if (bank == 0 || prg >= guest32(bank + 0x38)) {
        return 0;
    }
    uint32_t entry = guest32(bank + 0x3c + prg * 4), data = bank + (entry >> 8), from;
    out[0] = (uint8_t) entry;
    switch (out[0]) {
        case INST_PCM:
        case INST_PSG:
        case INST_NOISE:
        case INST_DIRECT_PCM:
        case INST_NULL:
            for (uint32_t i = 0; i < 10; i++) {
                out[2 + i] = (uint8_t) guest8(data + i);
            }
            return 1;
        case INST_DRUM_SET: {
            uint32_t low = guest8(data), high = guest8(data + 1);
            if (key < low || key > high) {
                return 0;
            }
            from = data + 2 + (key - low) * 12;
            break;
        }
        case INST_KEY_SPLIT: {
            uint32_t i = 0;
            while (i < 8 && key > guest8(data + i)) {
                i++;
            }
            if (i == 8) {
                return 0;
            }
            from = data + 8 + i * 12;
            break;
        }
        default:
            return 0;
    }
    for (uint32_t i = 0; i < 12; i++) {
        out[i] = (uint8_t) guest8(from + i);
    }
    return 1;
}

/* Wave `wave` of the bank's wave archive `archive` (0x724c, 0x73b4): its address, or 0. */
static uint32_t bank_wave(uint32_t bank, uint32_t archive, uint32_t wave)
{
    uint32_t arc = guest32(bank + 0x18 + archive * 8);
    if (arc == 0 || wave >= guest32(arc + 0x38)) {
        return 0;
    }
    uint32_t o = guest32(arc + 0x3c + wave * 4);
    return o == 0 ? 0 : o < 0x2000000u ? arc + o : o;
}

static uint32_t inst16(const uint8_t *inst, int at)
{
    return inst[at] | (uint32_t) inst[at + 1] << 8;
}

/* The channel set up for the instrument's note (0x728c); 0 when it cannot play it. */
static int note_setup(uint32_t c, uint32_t key, uint32_t velocity, int32_t length, uint32_t bank, const uint8_t *inst)
{
    uint32_t release = inst[10];
    int ok = 0;
    if (release == 0xff) {
        length = -1;
        release = 0;
    }
    switch (inst[0]) {
        case INST_PCM:
        case INST_DIRECT_PCM: {
            uint32_t wave = inst[0] == INST_PCM ? bank_wave(bank, inst16(inst, 4), inst16(inst, 2))
                                                : (inst16(inst, 4) << 16 | inst16(inst, 2));
            if (wave != 0) {
                channel_start_pcm(c, wave, length);
                ok = 1;
            }
            break;
        }
        case INST_PSG:
            ok = channel_start_psg(c, inst16(inst, 2), length);
            break;
        case INST_NOISE:
            ok = channel_start_noise(c, length);
            break;
        default:
            break;
    }
    if (!ok) {
        return 0;
    }
    set8(c + C_KEY, key);
    set8(c + C_ORIGINAL_KEY, inst[6]);
    set8(c + C_VELOCITY, velocity);
    set_attack(c, inst[7]);
    set_decay(c, inst[8]);
    set_sustain(c, inst[9]);
    set_release(c, release);
    set8(c + C_INIT_PAN, (uint32_t) inst[11] - 0x40);
    return 1;
}

/* A note on track `t` of player `p` (0x60c4): under a tie the track's channel takes the new key,
 * otherwise a channel is taken for the instrument and joins the track's list; then the track's
 * envelope and sweep settings. `length` is the note's ticks, or -1. */
static void note_on(uint32_t t, uint32_t p, uint32_t key, uint32_t velocity, int32_t length)
{
    uint32_t c = UINT32_MAX;
    sq.notes++;
    if (has(t, TF_TIE) && w32(t + T_CHANNELS) != 0) {
        c = work_offset(w32(t + T_CHANNELS));
        set8(c + C_KEY, key);
        set8(c + C_VELOCITY, velocity);
    }
    if (c == UINT32_MAX) {
        uint8_t inst[12];
        uint32_t mask;
        if (!bank_instrument(w32(p + P_BANK), w16(t + T_PRG), key, inst)) {
            return;
        }
        switch (inst[0]) {
            case INST_PCM:
            case INST_DIRECT_PCM:
                mask = CHANNEL_MASK_SAMPLE;
                break;
            case INST_PSG:
                mask = CHANNEL_MASK_PSG;
                break;
            case INST_NOISE:
                mask = CHANNEL_MASK_NOISE;
                break;
            default:
                return;
        }
        c = channel_alloc(mask & w16(t + T_CHANNEL_MASK), (int32_t) (w8(p + P_PRIO) + w8(t + T_PRIO)), has(t, TF_CHANNEL_MASK),
                          TRACK_CALLBACK, work_address(t));
        if (c == UINT32_MAX) {
            sq.no_channel++;
            return;
        }
        if (!note_setup(c, key, velocity, has(t, TF_TIE) ? -1 : length, w32(p + P_BANK), inst)) {
            set8(c + C_PRIO, 0);
            channel_clear_callback(c);
            return;
        }
        set32(c + C_NEXT, w32(t + T_CHANNELS));
        set32(t + T_CHANNELS, work_address(c));
    }
    if (w8(t + T_ATTACK) != 0xff) {
        set_attack(c, w8(t + T_ATTACK));
    }
    if (w8(t + T_DECAY) != 0xff) {
        set_decay(c, w8(t + T_DECAY));
    }
    if (w8(t + T_SUSTAIN) != 0xff) {
        set_sustain(c, w8(t + T_SUSTAIN));
    }
    if (w8(t + T_RELEASE) != 0xff) {
        set_release(c, w8(t + T_RELEASE));
    }
    int32_t sweep = ws16(t + T_SWEEP);
    if (has(t, TF_PORTA)) {
        sweep += (int32_t) ((uint32_t) ((int32_t) w8(t + T_PORTA_KEY) - (int32_t) key) << 22) >> 16;
    }
    set16(c + C_SWEEP_PITCH, (uint32_t) sweep);
    if (w8(t + T_PORTA_TIME) == 0) {
        set32(c + C_SWEEP_LENGTH, (uint32_t) length);
        set_flag(c + C_FLAGS, CF_AUTO_SWEEP, 0);
    } else {
        uint32_t time = w8(t + T_PORTA_TIME);
        int32_t s = ws16(c + C_SWEEP_PITCH);
        set32(c + C_SWEEP_LENGTH, (uint32_t) ((int32_t) (time * time * (uint32_t) (s < 0 ? -s : s)) >> 11));
    }
    set32(c + C_SWEEP_COUNTER, 0);
}

/* The track's settings given to its channels (0x6314): the volumes, the pitch bend and the pan
 * (to those not released, with the modulation), and with `release` a channel whose length ran
 * out is released. */
static void track_update_channels(uint32_t t, uint32_t p, int release)
{
    int32_t decay = (int16_t) (decibel(w8(p + P_VOLUME)) + decibel(w8(t + T_VOLUME)) + decibel(w8(t + T_VOLUME2)));
    int32_t decay2 = (int16_t) (ws16(t + T_EXT_FADER) + ws16(p + P_EXT_FADER));
    int32_t pitch = (int16_t) (ws16(t + T_EXT_PITCH) + ((ws8(t + T_PITCH_BEND) * (int32_t) (w8(t + T_BEND_RANGE) << 6)) >> 7));
    int32_t pan = ws8(t + T_PAN);
    if (w8(t + T_PAN_RANGE) != 0x7f) {
        pan = (pan * (int32_t) w8(t + T_PAN_RANGE) + 0x40) >> 7;
    }
    pan += ws8(t + T_EXT_PAN);
    pan = pan < -0x80 ? -0x80 : pan > 0x7f ? 0x7f : pan;
    for (uint32_t a = w32(t + T_CHANNELS); a != 0; a = w32(work_offset(a) + C_NEXT)) {
        uint32_t c = work_offset(a);
        set16(c + C_USER_DECAY2, (uint32_t) decay2);
        if (w8(c + C_ENV_STATUS) == 3) {
            continue;
        }
        set16(c + C_USER_DECAY, (uint32_t) decay);
        set16(c + C_USER_PITCH, (uint32_t) pitch);
        set8(c + C_USER_PAN, (uint32_t) pan);
        set8(c + C_PAN_RANGE, w8(t + T_PAN_RANGE));
        for (uint32_t i = 0; i < 6; i++) {
            set8(c + C_LFO + i, w8(t + T_MOD_TARGET + i));
        }
        if (w32(c + C_LENGTH) == 0 && release) {
            set8(c + C_PRIO, 1);
            set8(c + C_ENV_STATUS, 3);
        }
    }
}

/* The track's channels released (0x6698), at the rate `rate` unless it is negative. */
static void track_release_channels(uint32_t t, uint32_t p, int32_t rate)
{
    track_update_channels(t, p, 0);
    for (uint32_t a = w32(t + T_CHANNELS); a != 0; a = w32(work_offset(a) + C_NEXT)) {
        uint32_t c = work_offset(a);
        if (!has(c + C_FLAGS, CF_ACTIVE)) {
            continue;
        }
        if (rate >= 0) {
            set_release(c, (uint32_t) rate);
        }
        set8(c + C_PRIO, 1);
        set8(c + C_ENV_STATUS, 3);
    }
}

/* The track's channels let go of (0x665c): they sound on to their end without it. */
static void track_free_channels(uint32_t t)
{
    for (uint32_t a = w32(t + T_CHANNELS); a != 0; a = w32(work_offset(a) + C_NEXT)) {
        channel_clear_callback(work_offset(a));
    }
    set32(t + T_CHANNELS, 0);
}

/* A tick of the track's channels (0x572c): their lengths counted down, and a sweep timed by
 * ticks stepped. */
static void track_tick_channels(uint32_t t)
{
    for (uint32_t a = w32(t + T_CHANNELS); a != 0; a = w32(work_offset(a) + C_NEXT)) {
        uint32_t c = work_offset(a);
        if (ws32(c + C_LENGTH) > 0) {
            set32(c + C_LENGTH, w32(c + C_LENGTH) - 1);
        }
        if (!has(c + C_FLAGS, CF_AUTO_SWEEP) && ws32(c + C_SWEEP_COUNTER) < ws32(c + C_SWEEP_LENGTH)) {
            set32(c + C_SWEEP_COUNTER, w32(c + C_SWEEP_COUNTER) + 1);
        }
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

/* The player's track `i` closed (0x64fc): its channels released and let go of, the track
 * freed. */
static void track_close(uint32_t p, uint32_t i)
{
    uint32_t t = player_track(p, i);
    if (t == 0) {
        return;
    }
    track_release_channels(t, p, -1);
    track_free_channels(t);
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
    track_tick_channels(t);
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
            uint32_t velocity = next_byte(t);
            int32_t length = next_arg(t, p, kind >= 0 ? kind : ARG_VARLEN);
            int32_t key = (int32_t) c + (int8_t) w8(t + T_TRANSPOSE);
            if (!run) {
                continue;
            }
            key = key < 0 ? 0 : key > 127 ? 127 : key;
            if (!has(t, TF_MUTE) && play) {
                note_on(t, p, (uint32_t) key, velocity, length > 0 ? length : -1);
            }
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
                    case 0xc8: /* tie; the channels released and let go of */
                        set_flag(t, TF_TIE, v & 1);
                        track_release_channels(t, p, -1);
                        track_free_channels(t);
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

/* The tracks' settings given to their channels (0x62d0). */
static void player_update_channels(uint32_t p)
{
    for (uint32_t i = 0; i < TRACKS_PER_PLAYER; i++) {
        uint32_t t = player_track(p, i);
        if (t != 0) {
            track_update_channels(t, p, 1);
        }
    }
}

/* The sequencer's pass (0x7140): the started players stepped on a periodic pass unless paused,
 * their channels updated, then the shared work told which players are active. */
static void seq_main(int periodic)
{
    uint32_t status = 0;
    for (uint32_t no = 0; no < PLAYERS; no++) {
        uint32_t p = player_at(no);
        if (!has(p, PF_ACTIVE)) {
            continue;
        }
        if (has(p, PF_PREPARED)) {
            if (periodic && !has(p, PF_PAUSE)) {
                player_main(p);
            }
            player_update_channels(p);
        }
        if (has(p, PF_ACTIVE)) {
            status |= 1u << no;
        }
    }
    if (sq.shared_work != 0) {
        guest_store32(sq.shared_work + SW_PLAYER_STATUS, status);
    }
}

/* The time of the pass about to run; never earlier than the last one's. */
static void pass_at(uint64_t cycles)
{
    if (cycles > sq.now) {
        sq.now = cycles;
    }
}

/* The rest of a pass of the sound thread (0x4494), after its commands: the sequences, the
 * channels, the shared work's channel status (the channels playing) and capture status, and a
 * random number drawn. */
static void thread_pass(int periodic)
{
    seq_main(periodic);
    channel_main(periodic);
    if (sq.shared_work != 0) {
        uint32_t playing = 0;
        for (uint32_t no = 0; no < CHANNELS; no++) {
            playing |= hw_busy(no) ? 1u << no : 0;
        }
        guest_store16(sq.shared_work + SW_CHANNEL_STATUS, playing);
        guest_store16(sq.shared_work + SW_CAPTURE_STATUS, 0);
    }
    random16();
}

/* Driver info (0x781c): the state, where the ARM7 keeps it, each channel's control register
 * and the channels locked. */
static void read_driver_info(uint32_t to)
{
    for (uint32_t i = 0; i < WORK_SIZE; i += 4) {
        guest_store32(to + i, w32(i));
    }
    for (uint32_t i = 0; i < CHANNELS; i++) {
        hw_advance(i);
        guest_store32(to + WORK_SIZE + i * 4, sq.hw[i].control);
    }
    guest_store32(to + WORK_SIZE + 0x40, WORK_ADDRESS);
    guest_store32(to + WORK_SIZE + 0x44, sq.locked);
}

/* The driver's tables, from the ARM7 binary in the ROM (its offset and size in the header at
 * 0x30 and 0x3c). 0 on success. */
static int load_tables(const char *rom)
{
    FILE *f = rom != NULL ? fopen(rom, "rb") : NULL;
    uint8_t header[0x40];
    int ok = f != NULL && fread(header, 1, sizeof header, f) == sizeof header;
    uint32_t offset =
        ok ? (uint32_t) header[0x30] | header[0x31] << 8 | header[0x32] << 16 | (uint32_t) header[0x33] << 24 : 0;
    uint32_t size = ok ? (uint32_t) header[0x3c] | header[0x3d] << 8 | header[0x3e] << 16 | (uint32_t) header[0x3f] << 24 : 0;
    uint8_t *arm7 = ok && size > 0 && size <= 0x40000 ? malloc(size) : NULL;
    ok = arm7 != NULL && fseek(f, (long) offset, SEEK_SET) == 0 && fread(arm7, 1, size, f) == size &&
         TABLE_ATTACK + 0x20 - ARM7_WRAM_DELTA <= size;
    if (ok) {
        sq.driver = arm7;
        sq.driver_size = size;
    } else {
        free(arm7);
    }
    if (f != NULL) {
        fclose(f);
    }
    return ok ? 0 : -1;
}

int sequencer_init(const char *rom)
{
    const char *v = getenv("RUN_SEQUENCER");
    free(sq.driver);
    memset(&sq, 0, sizeof sq);
    sq.on = v != NULL && atoi(v) != 0;
    if (sq.on && load_tables(rom) != 0) {
        fprintf(stderr, "sequencer: cannot read the ARM7's sound driver from %s; the sequencer is off\n",
                rom ? rom : "(none)");
        sq.on = 0;
    }
    pitch_table();
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
        case CMD_MUTE_TRACK: { /* (0x6d68) muted with 1, released at once with 2 */
            uint32_t p = player_at(args[0]), mask = args[1];
            for (uint32_t i = 0; i < TRACKS_PER_PLAYER && mask != 0; i++, mask >>= 1) {
                uint32_t t = (mask & 1) ? player_track(p, i) : 0;
                if (t != 0) {
                    if (args[2] != 0) {
                        track_release_channels(t, p, 0x7f);
                        track_free_channels(t);
                    }
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
            channel_lock(args[0], args[1] & 1);
            break;
        case CMD_UNLOCK_CHANNEL:
            if (args[1] & 1) {
                sq.locked_weak &= ~args[0];
            } else {
                sq.locked &= ~args[0];
            }
            break;
        case CMD_STOP_UNLOCKED_CHANNEL:
            channel_drop(args[0]);
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
        case CMD_INVALIDATE_WAVE:
            channel_invalidate_wave(args[0], args[1]);
            break;
        case CMD_READ_DRIVER_INFO:
            read_driver_info(args[0]);
            break;
        default: /* the channels set up by the ARM9 itself, the timers, capture, alarms, volumes */
            break;
    }
}

void sequencer_before_list(void)
{
    pass_at(io_cycles());
    channel_sync();
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
        pass_at(sq.next_period);
        sq.next_period += PERIOD_CYCLES;
        sq.periods++;
        channel_sync();
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
            "players active %04x; %llu notes, %llu without a channel, %llu channels ended\n",
            (unsigned long long) sq.periods, (unsigned long long) sq.commands, (unsigned long long) sq.started,
            (unsigned long long) sq.finished, (unsigned long long) sq.ticks, (unsigned) active, (unsigned long long) sq.notes,
            (unsigned long long) sq.no_channel, (unsigned long long) sq.channels_ended);
}
