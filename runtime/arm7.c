/* The ARM7, simulated at the protocol level; see arm7.h.
 *
 * What the ARM9 expects was read from its SDK (config/adm-kr/arm9/autoload_2/symbols.txt
 * names the functions; the numbers below cite them) and, for the IPCSYNC handshake, from the
 * ARM7 binary in the ROM (extract/adm-kr/arm7/arm7.bin, PXI_InitFifo at 0x02383a28).
 *
 * The PXI FIFO word: bits 0-4 the tag (which subsystem), bit 5 the error flag, bits 6-31 the
 * data (PXI_SendWordByFifo, 0x0211938c). The tags this game uses:
 *   4   NVRAM, the firmware flash, through the game's own ARM7 component (func_020fff80
 *       builds the requests, Callback_NVRAM takes the result byte)
 *   5   RTC: command in bits 8-14, the raw clock registers are shared at 0x027ffde8
 *   6   touch panel: command in bits 0-7, result in 8-14, bit 24 "done"; samples at 0x027fffaa
 *   7   sound: command lists by address; completion is counted in the shared work
 *   8   power management: command in bits 8-14, result in 0-7
 *   0xa wireless manager, 0xb card backup (replies carry the error flag as "done"),
 *   0xc OS (reset), 0xd GBA cartridge, 0xe card pulled-out, 0xf WVR (wireless VRAM)
 */
#include "arm7.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "input.h"
#include "io.h"
#include "memory.h"

#define SHARED_FIFO_READY_ARM7 0x027fff8cu /* PXI_IsCallbackReady(tag, PXI_PROC_ARM7) */
#define SHARED_LOCK_INIT 0x027ffff0u       /* OSLockWord: flag, u16 owner, u16 extension */
#define SHARED_ARM7_VRAM_LOCK 0x027fffb8u  /* written by the ARM7's OS_InitLock */
/* RTCRawData (NitroSDK): the date first, then the time */
#define SHARED_RTC_DATE 0x027ffde8u
#define SHARED_RTC_TIME 0x027ffdecu
#define SHARED_TOUCH 0x027fffaau
#define SHARED_BUTTON_XY 0x027fffa8u

#define TAG_COUNT 32
#define NVRAM_SIZE 0x40000u

static struct {
    int sync_value; /* the handshake counter, 8 down to -1 (done) */
    int sync_delay; /* steps left before the ARM7 looks at the ARM9's echo again */
    int lock_done;  /* the lock word initialisation happened */
    uint64_t sent[TAG_COUNT], answered[TAG_COUNT], unanswered[TAG_COUNT];
    uint32_t first_data[TAG_COUNT];
    uint32_t last_data[TAG_COUNT];
    /* tag 4: the request being assembled, the status buffer the ARM9 named, the flash */
    uint32_t nv_parts[8];
    int nv_count;
    uint32_t nv_status_address;
    uint8_t nv_status;
    uint8_t *nvram;
    uint64_t nv_reads, nv_writes;
    /* tag 6: the request being assembled and the auto sampling state */
    uint32_t tp_command, tp_param, tp_auto, tp_index, tp_frame;
    /* tag 7: the shared work the sound driver reports in, and lists finished */
    uint32_t snd_shared_work;
    uint32_t snd_finished;
    /* tag 0xb: the ARM9's command block, the backup chip, and whether the next word is
       the block's address (it follows command 0) */
    uint32_t card_command;
    int card_expect_address;
    uint8_t *backup;
    uint64_t backup_reads, backup_writes;
} arm7;
#define BACKUP_SIZE ARM7_BACKUP_SIZE

static uint32_t rd32(uint32_t a)
{
    uint32_t v = 0;
    bus_read(a, 4, &v);
    return v;
}

static uint32_t rd16(uint32_t a)
{
    uint32_t v = 0;
    bus_read(a, 2, &v);
    return v;
}

static void wr32(uint32_t a, uint32_t v)
{
    bus_write(a, 4, v);
}

static void wr16(uint32_t a, uint32_t v)
{
    bus_write(a, 2, v);
}

static void wr8(uint32_t a, uint32_t v)
{
    bus_write(a, 1, v);
}

static uint32_t bcd(int v)
{
    return (uint32_t) ((v / 10) << 4 | (v % 10));
}

/* RUN_RTC="YYYY-MM-DD HH:MM:SS" pins the clock: it starts at that moment and advances with
 * the emulated bus clock (33513982 cycles a second), so two runs read the same times at the
 * same points and their frames can be compared. Without it the clock is the host's. */
static int rtc_pinned;
static int64_t rtc_base_seconds; /* the pinned start, in seconds since 1970-01-01 */

/* Days since 1970-01-01 of a proleptic Gregorian date, and back (H. Hinnant's algorithms);
 * plain arithmetic so a pinned clock does not depend on the host's time zone. */
static int64_t days_from_civil(int64_t y, int64_t m, int64_t d)
{
    y -= m <= 2;
    int64_t era = (y >= 0 ? y : y - 399) / 400;
    int64_t yoe = y - era * 400;
    int64_t doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    int64_t doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + doe - 719468;
}

static void civil_from_days(int64_t z, int *year, int *month, int *day)
{
    z += 719468;
    int64_t era = (z >= 0 ? z : z - 146096) / 146097;
    int64_t doe = z - era * 146097;
    int64_t yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    int64_t doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    int64_t mp = (5 * doy + 2) / 153;
    int64_t m = mp + (mp < 10 ? 3 : -9);
    *day = (int) (doy - (153 * mp + 2) / 5 + 1);
    *month = (int) m;
    *year = (int) (yoe + era * 400 + (m <= 2));
}

static void rtc_pin(void)
{
    const char *text = getenv("RUN_RTC");
    int y, mo, d, h, mi, se;
    if (text == NULL || text[0] == 0) {
        return;
    }
    if (sscanf(text, "%d-%d-%d %d:%d:%d", &y, &mo, &d, &h, &mi, &se) != 6 || y < 2000 || y > 2099 || mo < 1 || mo > 12 ||
        d < 1 || d > 31 || h < 0 || h > 23 || mi < 0 || mi > 59 || se < 0 || se > 59) {
        fprintf(stderr, "arm7: RUN_RTC is 'YYYY-MM-DD HH:MM:SS' in 2000-2099; using the host's clock\n");
        return;
    }
    rtc_pinned = 1;
    rtc_base_seconds = days_from_civil(y, mo, d) * 86400 + h * 3600 + mi * 60 + se;
}

/* The raw RTC registers as the ARM7 copies them: hour (bit 6 = afternoon), minute, second;
 * year, month, day, weekday (0 = Sunday), all BCD. */
static void rtc_update(void)
{
    int year, month, day, hour, minute, second, weekday;
    if (rtc_pinned) {
        int64_t t = rtc_base_seconds + (int64_t) (io_cycles() / 33513982u);
        int64_t days = t / 86400, rest = t % 86400;
        civil_from_days(days, &year, &month, &day);
        hour = (int) (rest / 3600);
        minute = (int) (rest / 60 % 60);
        second = (int) (rest % 60);
        weekday = (int) ((days + 4) % 7); /* 1970-01-01 was a Thursday */
    } else {
        time_t now = time(NULL);
        struct tm *tm = localtime(&now);
        year = tm->tm_year + 1900;
        month = tm->tm_mon + 1;
        day = tm->tm_mday;
        hour = tm->tm_hour;
        minute = tm->tm_min;
        second = tm->tm_sec;
        weekday = tm->tm_wday;
    }
    uint32_t h = bcd(hour) | (hour >= 12 ? 0x40u : 0);
    wr32(SHARED_RTC_TIME, h | bcd(minute) << 8 | bcd(second) << 16);
    wr32(SHARED_RTC_DATE, bcd(year % 100) | bcd(month) << 8 | bcd(day) << 16 | (uint32_t) weekday << 24);
}

/* The touch panel and X/Y as the ARM7 publishes them, from the input recording.
 *
 * A touch sample (SPITpData at 0x027fffaa) is the raw 12-bit ADC x in bits 0-11, y in
 * 12-23, bit 24 set while touching and bits 25-26 the validity (0 = valid). The game turns
 * raw values into pixels with the calibration in the user settings (0x027ffc80 + 0x58:
 * ADC x1, y1, screen x1, y1, ADC x2, y2, screen x2, y2), so the recording's pixel is taken
 * back through the same line to the ADC value that maps onto it. */
#define USER_SETTINGS 0x027ffc80u

static uint32_t touch_raw(int pixel, uint32_t adc1, uint32_t adc2, uint32_t scr1, uint32_t scr2)
{
    if (scr1 == scr2) {
        return 0;
    }
    int32_t raw =
        (int32_t) adc1 + (pixel - (int32_t) scr1) * ((int32_t) adc2 - (int32_t) adc1) / ((int32_t) scr2 - (int32_t) scr1);
    return raw < 0 ? 0u : raw > 4095 ? 4095u : (uint32_t) raw;
}

static void touch_sample(void)
{
    int x, y;
    uint32_t v = 0;
    if (input_touch(&x, &y)) {
        uint32_t u = USER_SETTINGS + 0x58;
        uint32_t rx = touch_raw(x, rd16(u), rd16(u + 6), rd16(u + 4) & 0xff, rd16(u + 10) & 0xff);
        uint32_t ry = touch_raw(y, rd16(u + 2), rd16(u + 8), rd16(u + 4) >> 8, rd16(u + 10) >> 8);
        v = rx | ry << 12 | 1u << 24;
    }
    /* halfword writes: the sample is not word-aligned in the shared area */
    wr16(SHARED_TOUCH, v & 0xffffu);
    wr16(SHARED_TOUCH + 2, v >> 16);
}

/* KEYXY as the ARM7 copies it to the shared area, already in the positions the ARM9's pad
 * reader merges with KEYINPUT: PAD_Read (func_020e9548) computes
 * ((KEYINPUT | shared) ^ 0x2fff) & 0x2fff and reads nothing while bit 15 is set. So KEYXY
 * bits 0-1 (X, Y) and 3 (debug) sit at 10-11 and 13, and bits 6-7 (pen up, hinge closed)
 * at 14-15; a held button and the pen down read 0, as in KEYXY. The debug button is never
 * pressed and the hinge is open. */
static void buttons_update(void)
{
    int x, y;
    uint32_t keyxy = 0x0008u | (~input_keys_xy() & 3u) | (input_touch(&x, &y) ? 0 : 0x40u);
    wr16(SHARED_BUTTON_XY, (keyxy & 0x0bu) << 10 | (keyxy & 0xc0u) << 8);
}

/* The firmware flash, as the game reads it through its ARM7 component: the header fields it
 * looks at (the console type at 0x1d, the user settings offset at 0x20) and two copies of
 * the user settings at 0x3fe00 and 0x3ff00, each with its update counter and CRC16 (GBATEK,
 * "DS Firmware Header", "DS Firmware User Settings"). The settings are those boot.c put at
 * 0x027ffc80, so the firmware agrees with its own copy. Everything else is erased flash. */
static uint32_t crc16(const uint8_t *p, size_t n)
{
    uint32_t crc = 0xffff;
    for (size_t i = 0; i < n; i++) {
        crc ^= p[i];
        for (int k = 0; k < 8; k++) {
            uint32_t carry = crc & 1;
            crc >>= 1;
            if (carry) {
                crc ^= 0xa001;
            }
        }
    }
    return crc & 0xffff;
}

static void nvram_init(void)
{
    arm7.nvram = malloc(NVRAM_SIZE);
    memset(arm7.nvram, 0xff, NVRAM_SIZE);
    memset(arm7.nvram, 0, 0x200);
    arm7.nvram[0x1d] = 0xff; /* console type: the original DS */
    arm7.nvram[0x20] = 0xc0; /* user settings at 0x7fc0 * 8 = 0x3fe00 */
    arm7.nvram[0x21] = 0x7f;
    for (int copy = 0; copy < 2; copy++) {
        uint8_t *block = arm7.nvram + 0x3fe00 + 0x100 * copy;
        uint8_t *settings = memory_host(0x027ffc80u, 0x70);
        memcpy(block, settings, 0x70);
        block[0x70] = (uint8_t) copy; /* update counter: the second copy is the newer */
        block[0x71] = 0;
        uint32_t crc = crc16(block, 0x70);
        block[0x72] = (uint8_t) crc;
        block[0x73] = (uint8_t) (crc >> 8);
    }
}

static void backup_load(const char *path)
{
    if (path == NULL || path[0] == 0) {
        return;
    }
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        fprintf(stderr, "arm7: cannot read the save %s\n", path);
        exit(2);
    }
    size_t n = fread(arm7.backup, 1, BACKUP_SIZE, f);
    fclose(f);
    fprintf(stderr, "arm7: save %s, %zu bytes\n", path, n);
}

void arm7_init(void)
{
    memset(&arm7, 0, sizeof(arm7));
    arm7.sync_value = 8;
    arm7.nv_status = 0x02; /* write enable latch set, nothing in progress */
    /* Every tag the ARM7's SDK and the game's ARM7 component register a callback for. */
    wr32(SHARED_FIFO_READY_ARM7, 0xfffffffeu);
    /* The ARM7 keeps the button/touch state in the shared area: X, Y and the debug button
       released (bits 0, 1, 3), pen up (bit 6), hinge open (bit 7 clear). */
    buttons_update();
    touch_sample();
    rtc_pin();
    rtc_update();
    nvram_init();
    /* the save chip, a 2 Mbit flash as this game has: erased, or holding the image RUN_SAVE
       names (a save file as emulators write it). Writes stay in memory; the file is only read. */
    arm7.backup = malloc(BACKUP_SIZE);
    memset(arm7.backup, 0xff, BACKUP_SIZE);
    backup_load(getenv("RUN_SAVE"));
}

static void reply(uint32_t tag, uint32_t data, int err)
{
    uint32_t word = (tag & 0x1f) | (err ? 0x20u : 0) | (data << 6);
    if (io_fifo_push_to_arm9(word)) {
        arm7.answered[tag]++;
    }
}

/* Tag 6, the touch panel. A request is one word, or two for auto sampling start: bit 25
 * marks the first word, bit 24 the last, bits 8-15 the command (0 sample now, 1 auto
 * sampling start with the samples per frame in the low byte, 2 stop, 3 stability) and bits
 * 0-15 its parameters. The ARM7 answers through its SPI reply helper (0x023896f8): data
 * 0x03000000 | (0x80 | command) << 8 | result, result 0 for success; while auto sampling, it
 * writes each sample to 0x027fffaa and sends command 0x10 for it (TPi_TpCallback). */
static void tp_reply(uint32_t command, uint32_t result)
{
    reply(6, 0x03000000u | ((0x80u | command) << 8) | (result & 0xff), 0);
}

static void tp_frame(void)
{
    if (arm7.tp_auto == 0 || arm7.tp_frame == io_frame()) {
        return;
    }
    arm7.tp_frame = io_frame();
    for (uint32_t i = 0; i < arm7.tp_auto; i++) {
        touch_sample();
        tp_reply(0x10, arm7.tp_index);
        arm7.tp_index = (arm7.tp_index + 1) % arm7.tp_auto;
    }
}

/* Tag 8, power management. A register read (PMi_ReadRegisterAsync, 0x0211de24) sends command
 * 0x65 with the register number in the low byte; PM_GetBattery (0x0211dbcc) reads register 1
 * and takes bit 0 as "battery low". The power management chip's registers as a console that
 * has just been switched on has them: 0 control (both backlights on), 1 battery status (not
 * low), 2 microphone amplifier (off), 3 amplifier gain (lowest). */
#define PM_READ_REGISTER 0x65u

static uint32_t pm_register(uint32_t reg)
{
    switch (reg) {
        case 0:
            return 0x0c;
        default:
            return 0;
    }
}

/* Tag 0xb, the backup chip. The ARM9 sends a command number (with the error flag, which
 * both sides use as "attention"), after command 0 the address of its command block, and
 * waits for a word back once the block's result (offset 0) is written (CARDi_Request,
 * 0x0211fd74). A transfer names a source at 0xc, a destination at 0x10 and a length at
 * 0x14 (CARDi_RequestStreamCommandCore): whichever side is below main RAM is the chip. */
static void card_request(uint32_t command)
{
    uint32_t block = arm7.card_command;
    if (block != 0 && command != 0) {
        uint32_t src = rd32(block + 0xc), dst = rd32(block + 0x10), len = rd32(block + 0x14);
        if (src < 0x02000000u && dst >= 0x02000000u && len <= BACKUP_SIZE) {
            for (uint32_t i = 0; i < len; i++) {
                wr8(dst + i, (src + i) < BACKUP_SIZE ? arm7.backup[src + i] : 0xff);
            }
            arm7.backup_reads++;
        } else if (dst < 0x02000000u && src >= 0x02000000u && len <= BACKUP_SIZE) {
            for (uint32_t i = 0; i < len && dst + i < BACKUP_SIZE; i++) {
                uint32_t v = 0;
                bus_read(src + i, 1, &v);
                arm7.backup[dst + i] = (uint8_t) v;
            }
            arm7.backup_writes++;
        }
        wr32(block, 0); /* CARD_RESULT_SUCCESS */
    }
    reply(0xb, 0, 1);
}

/* Tag 4, the flash. A request is up to six words: bit 25 marks the first, bit 24 the last,
 * bits 16-23 number the part and bits 0-15 carry it. The first part's byte 8-15 is the
 * operation (func_020fff80 at 0x020fff80 builds them; the names are by their effect):
 *   0x23 read:   hi address byte | address low | 0 | length | buffer hi | buffer lo
 *   0x25 write:  hi address byte | address low | length | buffer hi | buffer lo
 *   0x22 status: the address of a byte the ARM7 writes the flash status register to
 *   0x20, 0x21, 0x2d: write enable, the component's init, and a status refresh
 * The reply's low byte is the result; 0 is success. */
static void nvram_request(void)
{
    uint32_t p0 = arm7.nv_parts[0], op = (p0 >> 8) & 0xff;
    uint32_t *p = arm7.nv_parts;
    switch (op) {
        case 0x23: {
            uint32_t address = (p0 & 0xff) << 16 | (p[1] & 0xffff), length = p[3] & 0xffff;
            uint32_t buffer = (p[4] & 0xffff) << 16 | (p[5] & 0xffff);
            for (uint32_t i = 0; i < length; i++) {
                wr8(buffer + i, (address + i) < NVRAM_SIZE ? arm7.nvram[address + i] : 0xff);
            }
            arm7.nv_reads++;
            break;
        }
        case 0x25: {
            uint32_t address = (p0 & 0xff) << 16 | (p[1] & 0xffff), length = p[2] & 0xffff;
            uint32_t buffer = (p[3] & 0xffff) << 16 | (p[4] & 0xffff);
            for (uint32_t i = 0; i < length && address + i < NVRAM_SIZE; i++) {
                uint32_t v = 0;
                bus_read(buffer + i, 1, &v);
                arm7.nvram[address + i] = (uint8_t) v;
            }
            arm7.nv_writes++;
            break;
        }
        case 0x22:
            arm7.nv_status_address = (p0 & 0xff) << 24 | (p[1] & 0xffff) << 8 | ((p[2] >> 8) & 0xff);
            wr8(arm7.nv_status_address, arm7.nv_status);
            break;
        case 0x2d:
            if (arm7.nv_status_address) {
                wr8(arm7.nv_status_address, arm7.nv_status);
            }
            break;
        default: /* 0x20 write enable, 0x21 init: nothing to do */
            break;
    }
    reply(4, 0, 0);
}

/* Tag 7, the sound driver: a command list (24-byte commands: next, id, args) is executed
 * by the ARM7, which then counts it in the shared work (SND_RecvCommandReply reads word 0
 * of it, SNDi_GetFinishedCommandTag). Command 0x1d tells the driver where the shared work
 * is (SND_CommandInit). Nothing is played here. */
static void sound_list(uint32_t list)
{
    for (uint32_t cmd = list; cmd != 0 && (cmd >> 24) == 0x02; cmd = rd32(cmd)) {
        if (rd32(cmd + 4) == 0x1d) {
            arm7.snd_shared_work = rd32(cmd + 8);
        }
    }
    if (arm7.snd_shared_work != 0) {
        wr32(arm7.snd_shared_work, ++arm7.snd_finished);
    }
}

/* One FIFO word from the ARM9. Returns nonzero when something was answered. */
static int handle(uint32_t word)
{
    uint32_t tag = word & 0x1f, data = word >> 6;
    if (arm7.sent[tag]++ == 0) {
        arm7.first_data[tag] = data;
    }
    arm7.last_data[tag] = data;
    switch (tag) {
        case 4:
            if (data & (1u << 25)) {
                arm7.nv_count = 0;
            }
            if (arm7.nv_count < 8) {
                arm7.nv_parts[arm7.nv_count++] = data;
            }
            if (data & (1u << 24)) {
                nvram_request();
                return 1;
            }
            return 1;
        case 5: { /* RTC: answer the command with result 0 after refreshing the registers */
            uint32_t command = (data >> 8) & 0x7f;
            rtc_update();
            reply(5, command << 8, 0);
            return 1;
        }
        case 6: /* touch panel */
            if (data & (1u << 25)) {
                arm7.tp_command = (data >> 8) & 0xff;
                arm7.tp_param = data & 0xff;
            }
            if (data & (1u << 24)) {
                if (arm7.tp_command == 1) { /* auto sampling start: frequency per frame */
                    arm7.tp_auto = arm7.tp_param ? arm7.tp_param : 1;
                    arm7.tp_index = 0;
                } else if (arm7.tp_command == 2) {
                    arm7.tp_auto = 0;
                } else if (arm7.tp_command == 0) {
                    touch_sample(); /* sample now: the result is in the shared area */
                }
                tp_reply(arm7.tp_command, 0);
            }
            return 1;
        case 7:
            if (data >= 0x200000u) {
                sound_list(0x02000000u | (data & 0x3ffffffu));
            }
            return 1;
        case 8: { /* power management: echo the command with result 0, or a register's value */
            uint32_t command = (data >> 8) & 0x7f;
            if (command == PM_READ_REGISTER && (data & 0xffu) < 4) {
                /* the register's value comes back as command 0x70 + register (PMi_CommonCallback,
                   0x0211df10, stores it in the buffer PMi_ReadRegisterAsync named): no echo */
                uint32_t reg = data & 0xffu;
                reply(8, (0x70u + reg) << 8 | pm_register(reg), 0);
                return 1;
            }
            reply(8, command << 8, 0);
            return 1;
        }
        case 0xb:
            if (arm7.card_expect_address) {
                arm7.card_command = 0x02000000u | (data & 0x3ffffffu);
                arm7.card_expect_address = 0;
                card_request(0);
            } else if (data == 0) {
                arm7.card_expect_address = 1;
            } else {
                card_request(data);
            }
            return 1;
        case 0xd: /* GBA cartridge: command 1 (module info) acknowledged by its number */
            reply(0xd, data & 0x3f, 0);
            return 1;
        case 0xf: /* WVR: 0x10000 start up, 0x20000 terminate; the low byte is the result */
            reply(0xf, data & 0xff0000u, 0);
            return 1;
        default:
            return 0;
    }
}

void arm7_step(void)
{
    /* PXI_InitFifo's handshake: the ARM7 counts 8 down to 0 on its SYNC output, moving on
       each time the ARM9 echoes the current value; the ARM9 is done once it has seen at
       least five changes and the value is 0. */
    if (arm7.sync_value >= 0) {
        io_ipc_set_arm7_out((uint32_t) arm7.sync_value);
        if (arm7.sync_delay > 0) {
            arm7.sync_delay--; /* the ARM7 spins 1000 cycles before each look; the ARM9's
                                  echo has to land in between, which takes it a slice here */
        } else {
            arm7.sync_value = io_ipc_arm9_out() == (uint32_t) arm7.sync_value ? arm7.sync_value - 1 : 7;
            arm7.sync_delay = 4;
        }
    }
    /* OS_InitLock on the ARM7: once the ARM9 holds the lock word as owner 0x7f it records
       its VRAM claims and marks the word's extension (0x02380f48). */
    if (!arm7.lock_done && rd16(SHARED_LOCK_INIT + 4) == 0x7f) {
        wr32(SHARED_ARM7_VRAM_LOCK, 0xffffffffu);
        wr32(SHARED_ARM7_VRAM_LOCK + 4, 0xffff0000u);
        wr16(SHARED_LOCK_INIT + 6, 0xbf);
        arm7.lock_done = 1;
    }
    buttons_update();
    tp_frame();
    uint32_t word;
    while (io_fifo_pop_from_arm9(&word)) {
        if (!handle(word)) {
            arm7.unanswered[word & 0x1f]++;
        }
    }
}

const uint8_t *arm7_backup(uint64_t *writes)
{
    *writes = arm7.backup_writes;
    return arm7.backup;
}

void arm7_report(FILE *out)
{
    fprintf(out,
            "arm7: sync handshake %s, lock init %s, nvram %llu reads %llu writes, backup %llu reads %llu writes, "
            "sound lists %u\n",
            arm7.sync_value < 0 ? "done" : "not done", arm7.lock_done ? "done" : "not done",
            (unsigned long long) arm7.nv_reads, (unsigned long long) arm7.nv_writes, (unsigned long long) arm7.backup_reads,
            (unsigned long long) arm7.backup_writes, arm7.snd_finished);
    for (int tag = 0; tag < TAG_COUNT; tag++) {
        if (arm7.sent[tag] || arm7.answered[tag]) {
            fprintf(out, "  tag %2d: %6llu sent (first data %08x, last %08x), %6llu answered, %6llu unanswered\n", tag,
                    (unsigned long long) arm7.sent[tag], arm7.first_data[tag], arm7.last_data[tag],
                    (unsigned long long) arm7.answered[tag], (unsigned long long) arm7.unanswered[tag]);
        }
    }
}
