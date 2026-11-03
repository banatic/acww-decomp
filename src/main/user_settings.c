/* user_settings: 8 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020012bc @ 0x020012bc, 0x20 bytes, ARM
 * func_02001268 @ 0x02001268, 0x54 bytes, ARM
 * func_02001238 @ 0x02001238, 0x30 bytes, ARM
 * func_020010c0 @ 0x020010c0, 0x178 bytes, ARM
 * func_02001074 @ 0x02001074, 0x4c bytes, ARM
 * func_0200103c @ 0x0200103c, 0x38 bytes, ARM
 * func_02000e8c @ 0x02000e8c, 0x1b0 bytes, ARM
 * func_02000c98 @ 0x02000c98, 0x1f4 bytes, ARM
 */

#include "types.h"

struct UserSettingsOption {
    unsigned short language : 3;
    unsigned short agbLcd : 1;
    unsigned short detectCardRemoval : 1;
    unsigned short detectCartridgeRemoval : 1;
    unsigned short autoBoot : 1;
    unsigned short reserved : 4;
    unsigned short favoriteColorSet : 1;
    unsigned short touchCalibrated : 1;
    unsigned short languageSet : 1;
    unsigned short rtcSet : 1;
    unsigned short nicknameSet : 1;
    unsigned char timezone;
    unsigned char rtcClockAdjust;
    long long rtcOffset;
};

struct UserSettingsPage {
    unsigned char standardSettings[0x64];
    struct UserSettingsOption option;
    unsigned short saveCount;
    unsigned short crc16;
    unsigned char extensionVersion;
    unsigned char extendedLanguage;
    unsigned short validLanguageBitmap;
    unsigned char reserved[0x86];
    unsigned short extendedCrc16;
};

struct UserSettingsPage;

extern void OS_Init(void);
extern int PXI_IsCallbackReady(int, int);
extern void PXI_SetFifoRecvCallback(int, void (*)(int, int, int));
extern int data_0213fdc0;
extern void DC_InvalidateRange(void *c, int val);
extern void OS_SpinWait(int delay);
extern int PXI_SendWordByFifo(int cmd, int param, int zero);
extern void *OS_AllocFromArenaHi(int, int, int);
extern unsigned short GetCRC16(unsigned short start, const void *p, unsigned long len);
extern void OS_InitArena(void);
extern void *OS_GetArenaHi(int id);
extern void OS_SetArenaHi(int id, void *newHi);
extern void MIi_CpuClear32(u32 data, void *destp, u32 size);
extern void MIi_CpuCopy32(const void *srcp, void *destp, u32 size);

void func_02001268(void);
void func_02001238(int unused, int b, int c);
void func_02000c98(void);

void func_020012bc(void)
{
    OS_Init();
    func_02001268();
    func_02000c98();
}

void func_02001268(void)
{
    int r5 = 4;
    int r4 = 1;
    while (PXI_IsCallbackReady(r5, r4) == 0) {
        r5 = 4;
        r4 = 1;
    }
    PXI_SetFifoRecvCallback(4, func_02001238);
    {
        volatile unsigned short *p = (volatile unsigned short *) 0x04000208;
        unsigned short old = *p;
        *p = 1;
    }
}

void func_02001238(int unused, int b, int c)
{
    if (c == 0) {
        if ((b & 0xff) == 0) {
            data_0213fdc0 = 1;
            return;
        }
    }
    data_0213fdc0 = 2;
}

void func_020010c0(unsigned int a, unsigned int b, void *c)
{
    unsigned int mask = 0xffff;
    unsigned int c_val = (unsigned int) c;
    unsigned int a_hi = a >> 16;
    unsigned int a_lo = a & mask;
    unsigned int sb = 0x02002300 | (a_hi & 0xff);
    unsigned int fp = 0x40000 | (c_val >> 16);
    unsigned int b_hi = b >> 16;
    unsigned int b_lo = b & mask;
    unsigned int r8 = 0x10000 | a_lo;
    unsigned int r7 = 0x20000 | b_hi;
    unsigned int r6 = 0x30000 | b_lo;
    unsigned int val2 = 0x01050000 | (c_val & mask);
    int val3 = 0x20;
    int zero = 0;
    int four = 4;
    int val4 = 1;

    while (1) {
        int ok;
        (*(volatile int *) &data_0213fdc0) = zero;
        DC_InvalidateRange(c, val3);

        goto check_start;
        do {
            OS_SpinWait(0x186a0);
        check_start:
            if (PXI_SendWordByFifo(four, sb, zero) < 0) {
                ok = zero;
            } else if (PXI_SendWordByFifo(four, r8, zero) < 0) {
                ok = zero;
            } else if (PXI_SendWordByFifo(four, r7, zero) < 0) {
                ok = zero;
            } else if (PXI_SendWordByFifo(four, r6, zero) < 0) {
                ok = zero;
            } else if (PXI_SendWordByFifo(four, fp, zero) < 0) {
                ok = zero;
            } else if (PXI_SendWordByFifo(four, val2, zero) < 0) {
                ok = zero;
            } else {
                ok = val4;
            }
        } while (ok == 0);

        while ((*(volatile int *) &data_0213fdc0) == 0) {
        }

        if ((*(volatile int *) &data_0213fdc0) == 1) {
            return;
        }
    }
}

int func_02001074(void)
{
    void *p;
    unsigned char c;

    p = OS_AllocFromArenaHi(0, 1, 0x20);
    func_020010c0(0x1d, 1, p);
    c = *(unsigned char *) p;
    if (c == 0xff) {
        return 0;
    }
    return (c & 0x50) != 0;
}

unsigned short func_0200103c(void)
{
    unsigned char v;
    unsigned short r = 0;

    v = *(unsigned char *) 0x027ffe1d;
    if (v == 0x80) {
        r |= 0x40;
    } else if (v == 0x40) {
        r |= 0x80;
    }
    return r;
}

// The SDK option record is 12 bytes with a three-bit language field.
int func_02000e8c(struct UserSettingsPage *base)
{
    unsigned short i;
    int valid;
    unsigned short mask;
    int m40;
    unsigned char t;
    unsigned int cv;

    valid = 0;

    if (func_02001074() != 0) {
        mask = func_0200103c();
        m40 = mask & 0x40;
        for (i = 0; i < 2; i = (unsigned short) (i + 1)) {
            cv = GetCRC16(0xffff, &base[i], 0x70);
            if (cv != base[i].crc16) {
                continue;
            }
            if (base[i].saveCount >= 0x80) {
                continue;
            }
            cv = GetCRC16(0xffff, &base[i].extensionVersion, 0x8a);
            if (cv != base[i].extendedCrc16) {
                continue;
            }
            if (((1u << base[i].extendedLanguage) & base[i].validLanguageBitmap) == 0) {
                continue;
            }
            if ((mask & base[i].validLanguageBitmap) != 0) {
                base[i].option.language = base[i].extendedLanguage;
            }
            if ((m40 & ~base[i].validLanguageBitmap) != 0) {
                return 3;
            }
            valid = valid | (1 << i);
        }
    } else {
        if ((func_0200103c() & 0x40) != 0) {
            return 3;
        }
        i = 0;
        do {
            cv = GetCRC16(0xffff, &base[i], 0x70);
            if (cv == base[i].crc16) {
                if (base[i].saveCount < 0x80) {
                    valid = valid | (1 << i);
                }
            }
            i = (unsigned short) (i + 1);
        } while (i < 2);
    }

    switch (valid) {
        case 1:
        case 2:
            return valid;
        case 3:
            t = (unsigned char) ((base[0].saveCount + 1) & 0x7f);
            if (t == base[1].saveCount) {
                return 2;
            }
            return 1;
    }
    return 0;
}

void func_02000c98(void)
{
    u32 *addr;
    u32 *shift;
    u32 *cmd;
    u32 *len;
    u8 *buf;
    u8(*pages)[0x100];
    int *gen;
    int i;
    void *hi;

    OS_InitArena();
    hi = OS_GetArenaHi(0);
    addr = (u32 *) OS_AllocFromArenaHi(0, 4, 4);
    buf = (u8 *) OS_AllocFromArenaHi(0, 0x200, 0x20);
    gen = (int *) OS_AllocFromArenaHi(0, 4, 0x20);
    cmd = (u32 *) OS_AllocFromArenaHi(0, 4, 0x20);
    len = (u32 *) OS_AllocFromArenaHi(0, 4, 0x20);
    shift = (u32 *) OS_AllocFromArenaHi(0, 4, 0x20);

    *cmd = 0x20;
    *len = 2;
    *shift = 3;
    func_020010c0(*cmd, *len, addr);
    *addr <<= *shift;
    func_020010c0(*addr, 0x100, buf);
    func_020010c0(*addr + 0x100, 0x100, buf + 0x100);

    pages = (u8(*)[0x100]) buf;
    *gen = func_02000e8c((struct UserSettingsPage *) buf);
    if (*gen >= 3) {
        volatile u32 fill = 0xffffffff;
        MIi_CpuClear32(fill, (void *) 0x027ffc80, 0x74);
    } else if (*gen != 0) {
        if (*(pages[*gen] - 0xe6) < 10u) {
            for (i = 10; i > *(pages[*gen] - 0xe6); i--) {
                *(u16 *) (pages[*gen] + (i << 1) - 0xfc) = 0;
            }
        }
        if (*(pages[*gen] - 0xb0) < 26u) {
            for (i = 26; i > *(pages[*gen] - 0xb0); i--) {
                *(u16 *) (pages[*gen] + (i << 1) - 0xe6) = 0;
            }
        }
        MIi_CpuCopy32(pages[*gen] - 0x100, (void *) 0x027ffc80, 0x74);
    } else {
        volatile u32 zero = 0;
        MIi_CpuClear32(zero, (void *) 0x027ffc80, 0x74);
    }
    OS_SetArenaHi(0, hi);
}
