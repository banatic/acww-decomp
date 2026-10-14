/* The firmware's hand-off to the game; see boot.h.
 *
 * The ARM9 program is loaded straight from the ROM, compressed as it is there: the game's own
 * crt0 (Entry, 0x02000800) decompresses it backwards and copies the autoload modules to
 * ITCM, DTCM and their main RAM addresses, exactly as on the console. The ROM dump's secure
 * area is already decrypted, with its first eight bytes replaced by 0xe7ffdeff as the
 * firmware leaves them. */
#include "boot.h"

#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "memory.h"

static uint32_t entry_address;

static uint32_t le32(const uint8_t *p)
{
    return (uint32_t) p[0] | ((uint32_t) p[1] << 8) | ((uint32_t) p[2] << 16) | ((uint32_t) p[3] << 24);
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

/* The user settings the firmware copies from NVRAM (GBATEK, "DS Firmware User Settings"):
 * a player called PLAYER, born January 1st, Korean language, with a linear touch screen
 * calibration. The console's real values are not in the ROM; these are plausible ones. */
static void user_settings(void)
{
    static const char name[] = "PLAYER";
    uint32_t u = BOOT_USER_SETTINGS;
    wr8(u + 0x00, 5); /* version */
    wr8(u + 0x02, 0); /* favourite colour */
    wr8(u + 0x03, 1); /* birthday month */
    wr8(u + 0x04, 1); /* birthday day */
    for (int i = 0; i < 6; i++) {
        wr16(u + 0x06 + 2 * (uint32_t) i, (uint8_t) name[i]);
    }
    wr16(u + 0x1a, 6);      /* nickname length */
    wr16(u + 0x50, 0);      /* message length */
    wr8(u + 0x52, 0);       /* alarm hour */
    wr8(u + 0x53, 0);       /* alarm minute */
    wr16(u + 0x56, 0);      /* alarm off */
    wr16(u + 0x58, 0x0200); /* touch: ADC x1, y1 at screen 16, 16 */
    wr16(u + 0x5a, 0x0200);
    wr8(u + 0x5c, 16);
    wr8(u + 0x5d, 16);
    wr16(u + 0x5e, 0x0e00); /* ADC x2, y2 at screen 240, 176 */
    wr16(u + 0x60, 0x0e00);
    wr8(u + 0x62, 240);
    wr8(u + 0x63, 176);
    wr16(u + 0x64, 7); /* language 7 (Korean firmware), backlight low, boot menu on */
    wr8(u + 0x66, 26); /* year offset from 2000 */
    wr32(u + 0x68, 0); /* RTC offset */
}

int boot_init(const char *rom_path, ArmCpu *cpu)
{
    FILE *f = fopen(rom_path, "rb");
    if (f == NULL) {
        return -1;
    }
    uint8_t header[0x200];
    if (fread(header, 1, sizeof(header), f) != sizeof(header)) {
        fclose(f);
        return -1;
    }
    uint32_t rom_offset = le32(header + 0x20);
    entry_address = le32(header + 0x24);
    uint32_t load = le32(header + 0x28);
    uint32_t size = le32(header + 0x2c);
    uint8_t *dst = memory_host(load, size);
    if (dst == NULL) {
        fclose(f);
        return -1;
    }
    fseek(f, (long) rom_offset, SEEK_SET);
    if (fread(dst, 1, size, f) != size) {
        fclose(f);
        return -1;
    }
    fclose(f);

    /* The header copy and the card identification the firmware stores beside it. */
    memcpy(memory_host(BOOT_HEADER_COPY, sizeof(header)), header, sizeof(header));
    uint32_t chip_id = io_card_chip_id();
    wr32(BOOT_CHIP_ID_1, chip_id);
    wr32(BOOT_CHIP_ID_2, chip_id);
    wr32(BOOT_CHIP_ID_3, chip_id);
    wr32(BOOT_CHIP_ID_4, chip_id);
    wr16(BOOT_SECURE_CRC, le32(header + 0x6c) & 0xffffu);
    wr16(BOOT_HEADER_CRC, le32(header + 0x15c) >> 16);
    wr16(BOOT_SECURE_CRC_2, le32(header + 0x6c) & 0xffffu);
    wr16(BOOT_HEADER_CRC_2, le32(header + 0x15c) >> 16);
    wr16(BOOT_INDICATOR, 1); /* a normal boot from the card */
    user_settings();

    /* Registers the BIOS and firmware leave set: POSTFLG once the BIOS has booted,
       EXMEMCNT with both slots given to the ARM7 and WRAMCNT with the shared WRAM too. */
    wr16(0x04000300, 1);
    wr16(0x04000204, 0xe880);
    wr8(0x04000247, 3);

    arm_init(cpu);
    cpu->r[15] = entry_address & ~1u;
    return 0;
}

uint32_t boot_entry(void)
{
    return entry_address;
}

int boot_verify(const char *manifest, FILE *out)
{
    FILE *f = fopen(manifest, "r");
    if (f == NULL) {
        fprintf(out, "boot: no manifest %s, modules not compared\n", manifest);
        return -1;
    }
    char line[640], name[16], path[512];
    unsigned base;
    int failures = 0;
    while (fgets(line, sizeof(line), f) != NULL) {
        if (sscanf(line, "%15s %x %511[^\r\n]", name, &base, path) != 3 || strncmp(name, "ov", 2) == 0) {
            continue;
        }
        FILE *m = fopen(path, "rb");
        if (m == NULL) {
            fprintf(out, "boot: cannot read %s\n", path);
            failures++;
            continue;
        }
        fseek(m, 0, SEEK_END);
        long size = ftell(m);
        fseek(m, 0, SEEK_SET);
        uint8_t *image = malloc((size_t) size + 1);
        if (image == NULL || fread(image, 1, (size_t) size, m) != (size_t) size) {
            fclose(m);
            free(image);
            failures++;
            continue;
        }
        fclose(m);
        uint8_t *mem = memory_host(base, (uint32_t) size);
        long first = -1;
        /* The extracted main module has the "compressed static end" word of the SDK module
           parameters (0x14 before the 0xdec00621 signature) zeroed, since it is unpacked;
           the ROM's copy keeps the real end address. Nothing else may differ. */
        long skip = -1;
        for (long i = 0; i + 8 <= size; i += 4) {
            if (le32(image + i) == 0xdec00621u && le32(image + i + 4) == 0x2106c0deu) {
                skip = i - 0x1c + 0x14;
                break;
            }
        }
        if (mem != NULL) {
            for (long i = 0; i < size; i++) {
                if (mem[i] != image[i] && (i < skip || i >= skip + 4)) {
                    first = i;
                    break;
                }
            }
        }
        if (mem == NULL || first >= 0) {
            fprintf(out, "boot: %s differs from memory at %08lx\n", name, (unsigned long) base + (unsigned long) first);
            failures++;
        } else {
            fprintf(out, "boot: %s matches memory (%ld bytes at %08x)\n", name, size, base);
        }
        free(image);
    }
    fclose(f);
    return failures;
}
