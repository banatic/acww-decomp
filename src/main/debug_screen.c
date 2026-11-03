/* debug_screen: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020015fc @ 0x020015fc, 0x12 bytes, Thumb
 * func_020015c8 @ 0x020015c8, 0x34 bytes, Thumb
 * func_020014b4 @ 0x020014b4, 0x114 bytes, Thumb
 * func_0200149c @ 0x0200149c, 0x18 bytes, Thumb
 * func_02001324 @ 0x02001324, 0x178 bytes, Thumb
 * func_020012ec @ 0x020012ec, 0x38 bytes, Thumb
 */

#include "types.h"

#define REG16(addr) (*(volatile unsigned short *) (addr))
#define REG32(addr) (*(volatile unsigned int *) (addr))
#define gInput2 (*(unsigned short *) 0x027fffa8)

extern void MIi_CpuClearFast(unsigned int data, void *dest, unsigned int size);
extern unsigned int data_0213fdd0;
extern unsigned int data_0213fddc;
extern void func_02053f20(void);
extern void GX_SetBankForBG(unsigned int);
extern void GX_SetBankForSubBG(unsigned int);
extern void func_02112d48(void *, unsigned int, unsigned int);
extern void func_02112ce0(void *, unsigned int, unsigned int);
extern void GX_LoadBGPltt(void *, unsigned int, unsigned int);
extern void GXS_LoadBGPltt(void *, unsigned int, unsigned int);
extern unsigned int G2_GetBG1ScrPtr(void);
extern unsigned int G2S_GetBG1ScrPtr(void);
extern void GX_DispOn(void);
extern unsigned char data_020df71c[];
extern unsigned char data_020e171c[];
extern unsigned char data_0213fdc4;
extern unsigned int data_0213fdc8;
extern void func_02001610(void);
extern void func_0200184c(void);
extern void func_0204f8b8(void);
extern int OS_GetProcMode(void);
extern void func_020e9e78(unsigned int arg);
extern unsigned int data_021fbe8c;
extern unsigned int data_021fbe94;
extern unsigned int sSubOBJExtPltt;
extern u64 OS_GetTick(void);
extern u32 data_0213fdd4;

void func_020015fc(unsigned int data, void *dest, unsigned int size)
{
    volatile unsigned int fill = data;
    MIi_CpuClearFast(fill, dest, size);
}

void func_020015c8(void)
{
    unsigned int a;
    a = data_0213fddc;
    func_020015fc(0x007f007f, (void *) data_0213fdd0, 0x00000800);
    func_020015fc(0x007f007f, (void *) a, 0x00000800);
}

void func_020014b4(void)
{
    func_02053f20();
    REG16(0x04000304) |= 0x0001;
    REG16(0x04000050) = 0;
    REG16(0x04001050) = 0;
    GX_SetBankForBG(0x40);
    GX_SetBankForSubBG(0x80);
    REG32(0x04000000) = (REG32(0x04000000) & 0xffffe0ff) | 0x00000200;
    REG32(0x04001000) = (REG32(0x04001000) & 0xffffe0ff) | 0x00000200;
    REG16(0x0400000a) = (REG16(0x0400000a) & 0x43) | 0x0400;
    REG16(0x0400100a) = (REG16(0x0400100a) & 0x43) | 0x0400;
    func_02112d48((void *) data_020df71c, 0, 0x1000);
    func_02112ce0((void *) data_020df71c, 0, 0x1000);
    GX_LoadBGPltt((void *) data_020e171c, 0x1a0, 0x60);
    GXS_LoadBGPltt((void *) data_020e171c, 0x1a0, 0x60);
    REG16(0x05000000) = 0x7c00;
    REG16(0x05000018) = 0x7c00;
    REG16(0x05000400) = 0x7c00;
    REG16(0x05000418) = 0x7c00;
    data_0213fdd0 = G2_GetBG1ScrPtr();
    data_0213fddc = G2S_GetBG1ScrPtr();
    func_020015c8();
    GX_DispOn();
    REG32(0x04001000) |= 0x00010000;
}

void func_0200149c(void)
{
    while ((int) *(volatile unsigned short *) 0x04000006 >= 0xC0)
        ;
    while ((int) *(volatile unsigned short *) 0x04000006 < 0xC0)
        ;
}

void func_02001324(void)
{
    unsigned char state = data_0213fdc4;
    unsigned int keys = (unsigned short) (((*(volatile unsigned short *) 0x04000130 | gInput2) ^ 0x2fff) & 0x2fff) & 0x3ff;
    unsigned int prev = data_0213fdc8;
    unsigned int pressed = keys & (prev ^ keys);
    data_0213fdc8 = keys;

    switch (state) {
        case 0:
            if (pressed & 0x2000) {
                state = 5;
            }
            if (keys == 0x321) {
                state++;
            }
            break;
        case 1:
            if (keys == 0) {
                state++;
            }
            break;
        case 2:
            if ((keys & ~0x82) != 0) {
                state = 0;
            } else if (keys == 0x82) {
                state++;
            }
            break;
        case 3:
            if (keys == 0) {
                state++;
            }
            break;
        case 4:
            if ((keys & ~0xc) != 0) {
                state = 0;
            } else if (keys == 0xc) {
                state++;
            }
            break;
        case 5:
            func_020014b4();
            func_02001610();
            state++;
            // fall through
        case 6:
            func_02001610();
            func_0200184c();
            {
                unsigned int k4 = keys & 4;
                if (k4 != 0) {
                    if ((pressed & 1) != 0) {
                        if (k4 != 0) {
                            if (OS_GetProcMode() == 0x1f) {
                                unsigned int g1v = data_021fbe8c;
                                unsigned int g2v = data_021fbe94;
                                unsigned int g3v = sSubOBJExtPltt;
                                if (keys & 0x20) {
                                    func_020e9e78(g1v);
                                } else if (keys & 0x10) {
                                    func_020e9e78(g3v);
                                } else if (keys & 0x40) {
                                    func_020e9e78(g2v);
                                }
                            }
                        }
                    }
                    if ((pressed & 2) != 0) {
                        if (k4 != 0) {
                            func_0204f8b8();
                        }
                    }
                }
            }
            break;
    }

    func_0200149c();
    data_0213fdc4 = state;
}

void func_020012ec(void)
{
    volatile u16 *reg;
    u64 tick;

    reg = (volatile u16 *) 0x04000208;
    (void) *reg;
    *reg = 0;
    tick = OS_GetTick();
    tick <<= 6;
    data_0213fdd4 = tick / 0x82ea;
    while (1) {
        func_02001324();
    }
}
