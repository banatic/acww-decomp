/* display_layers_2: 15 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02002e04 @ 0x02002e04, 0x10 bytes, Thumb
 * func_02002dc8 @ 0x02002dc8, 0x3c bytes, Thumb
 * func_02002d8c @ 0x02002d8c, 0x3c bytes, Thumb
 * func_02002d50 @ 0x02002d50, 0x3c bytes, Thumb
 * func_02002d14 @ 0x02002d14, 0x3a bytes, Thumb
 * func_02002cd8 @ 0x02002cd8, 0x3c bytes, Thumb
 * func_02002ca4 @ 0x02002ca4, 0x32 bytes, Thumb
 * func_02002c6c @ 0x02002c6c, 0x38 bytes, Thumb
 * func_02002c4c @ 0x02002c4c, 0x20 bytes, Thumb
 * func_02002bd0 @ 0x02002bd0, 0x7c bytes, Thumb
 * func_02002b40 @ 0x02002b40, 0x8e bytes, Thumb
 * func_02002a88 @ 0x02002a88, 0xb6 bytes, Thumb
 * func_020029e8 @ 0x020029e8, 0xa0 bytes, Thumb
 * func_020028bc @ 0x020028bc, 0x12c bytes, Thumb
 * func_0200284c @ 0x0200284c, 0x6e bytes, Thumb
 */

#include "types.h"

#define REG16(addr) (*(volatile unsigned short *) (addr))

extern void func_020e993c(int, int);
extern int func_02064b2c(int, int, int, int *);
extern void DC_FlushRange(unsigned char *p, int r);
extern void GX_LoadOBJPltt(unsigned char *p, int q, int r);
extern void GXS_LoadOBJPltt(unsigned char *p, int q, int r);
extern void GX_LoadBGPltt(unsigned char *p, int q, int r);
extern void GXS_LoadBGPltt(unsigned char *p, int q, int r);
extern void func_02113088(int, int, int);
extern void GX_LoadBG2Scr(int, int, int);
extern void func_02112ee8(int, int, int);
extern void func_021130f0(int, int, int);
extern void func_02113020(int, int, int);
extern void func_02112f50(int, int, int);
extern void func_02112e80(int, int, int);
extern void func_02112b40(const void *pSrc, u32 offset, u32 szByte);
extern void func_02112ba8(const void *pSrc, u32 offset, u32 szByte);
extern void func_02112c10(const void *pSrc, u32 offset, u32 szByte);
extern void GX_LoadBG2Char(const void *pSrc, u32 offset, u32 szByte);
extern void func_02112ce0(const void *pSrc, u32 offset, u32 szByte);
extern void func_02112d48(const void *pSrc, u32 offset, u32 szByte);
extern void func_02112db0(const void *pSrc, u32 offset, u32 szByte);
extern void GX_LoadOBJ(const void *pSrc, u32 offset, u32 szByte);
extern void GXS_LoadOBJ(const void *pSrc, u32 offset, u32 szByte);
extern void func_02001e74(int, int);
extern void func_02001e54(int, int);
extern void func_02001e34(int, int);
extern void func_02001e14(int, int);
extern void func_02001df4(int, int);
extern void func_02001dd4(int, int);
extern void func_02001db8(int, int);

int func_02002bd0(unsigned char *base, unsigned int mode, int a, int b, unsigned char c);
int func_02002b40(int a0, int a1, int a2, int a3);
int func_02002a88(u32 base, int type, u32 col0, u32 col1, u32 col2);

int func_02002e04(unsigned int r0)
{
    if (r0 <= 2 || r0 == 7) {
        return 1;
    } else {
        return 0;
    }
}

int func_02002dc8(unsigned int x)
{
    switch (x) {
        case 3:
            return 0;
        case 0:
        case 4:
            return 1;
        case 1:
        case 5:
            return 2;
        case 2:
        case 6:
            return 3;
        case 7:
        case 8:
            return 4;
        default:
            return 0;
    }
}

int func_02002d8c(unsigned int param)
{
    switch (param) {
        case 3:
            return 1;
        case 0:
        case 4:
            return 2;
        case 1:
        case 5:
            return 4;
        case 2:
        case 6:
            return 8;
        case 7:
        case 8:
            return 16;
        default:
            return 1;
    }
}

unsigned char func_02002d50(unsigned int param)
{
    switch (param) {
        case 3:
            return 1;
        case 0:
        case 4:
            return 2;
        case 1:
        case 5:
            return 4;
        case 2:
        case 6:
            return 8;
        case 7:
        case 8:
            return 16;
        default:
            return 1;
    }
}

int func_02002d14(int a0, int a1, int a2, int a3, unsigned char a4, unsigned char a5)
{
    int t1, t2;
    t1 = func_02064b2c(a0, a1, ~3, 0);
    t2 = func_02002bd0((unsigned char *) t1, a2, a3, (unsigned char) a4, a5);
    func_020e993c(a1, t1);
    return t2;
}

int func_02002cd8(int p0, int a, int b, int c, unsigned char d5)
{
    int tmp[2];
    char *base;
    char *slot;
    int result;

    base = (char *) func_02064b2c(p0, a, -4, (int *) tmp);
    slot = base;
    slot += c << 5;
    result = func_02002bd0((unsigned char *) slot, b, (unsigned char) d5, (unsigned char) d5, d5);
    func_020e993c(a, (int) base);
    return result;
}

int func_02002ca4(int a0, int a1, int a2)
{
    int local;
    int x;
    int y;

    x = func_02064b2c(a0, a1, ~3, &local);
    y = func_02002b40(x, a2, local, 0);
    func_020e993c(a1, x);
    return y;
}

int func_02002c6c(int p1, int p2, int p3, int p4, int p5, int p6)
{
    int temp[2];
    int s;
    int r;

    s = func_02064b2c(p1, p2, ~3, temp);
    r = func_02002a88(s, p3, p4, p5, p6);
    func_020e993c(p2, s);
    return r;
}

int func_02002c4c(int a1, int a2, int a3, int a4, int a5, int a6)
{
    int local0;
    int local1;

    local0 = a5 << 1;
    local1 = (a6 << 1) + 1;
    return func_02002c6c(a1, a2, a3, a4 << 1, local0, local1);
}

int func_02002bd0(unsigned char *base, unsigned int mode, int a, int b, unsigned char c)
{
    unsigned char *p;
    int q, r;

    p = base + ((b - a) << 5);
    r = ((c - b + 1) << 5);
    q = b << 5;

    DC_FlushRange(p, r);

    if (mode == 7) {
        GX_LoadOBJPltt(p, q, r);
    } else if (mode == 8) {
        GXS_LoadOBJPltt(p, q, r);
    } else if (mode <= 2) {
        if (q == 0) {
            q = 2;
            r -= 2;
            p += 2;
        }
        GX_LoadBGPltt(p, q, r);
    } else if (mode <= 6) {
        if (q == 0) {
            q = 2;
            r -= 2;
            p += 2;
        }
        GXS_LoadBGPltt(p, q, r);
    }

    return 1;
}

int func_02002b40(int a0, int a1, int a2, int a3)
{
    DC_FlushRange((unsigned char *) a0, a2);
    switch (a1) {
        case 0:
            func_02113088(a0, a3, a2);
            break;
        case 1:
            GX_LoadBG2Scr(a0, a3, a2);
            break;
        case 2:
            func_02112ee8(a0, a3, a2);
            break;
        case 3:
            func_021130f0(a0, a3, a2);
            break;
        case 4:
            func_02113020(a0, a3, a2);
            break;
        case 5:
            func_02112f50(a0, a3, a2);
            break;
        case 6:
            func_02112e80(a0, a3, a2);
            break;
        default:
            break;
    }
    return 1;
}

int func_02002a88(u32 base, int type, u32 col0, u32 col1, u32 col2)
{
    u32 addr = base + ((col1 - col0) << 5);
    u32 size = ((col2 - col1) + 1) << 5;
    u32 offset = col1 << 5;

    DC_FlushRange((unsigned char *) ((void *) addr), size);

    switch (type) {
        case 0:
            func_02112d48((const void *) addr, offset, size);
            break;
        case 1:
            GX_LoadBG2Char((const void *) addr, offset, size);
            break;
        case 2:
            func_02112ba8((const void *) addr, offset, size);
            break;
        case 3:
            func_02112db0((const void *) addr, offset, size);
            break;
        case 4:
            func_02112ce0((const void *) addr, offset, size);
            break;
        case 5:
            func_02112c10((const void *) addr, offset, size);
            break;
        case 6:
            func_02112b40((const void *) addr, offset, size);
            break;
        case 7:
            GX_LoadOBJ((const void *) addr, offset, size);
            break;
        case 8:
            GXS_LoadOBJ((const void *) addr, offset, size);
            break;
        default:
            break;
    }
    return 1;
}

void func_020029e8(int layer, int priority)
{
    switch (layer) {
        case 0:
            REG16(0x0400000a) = (REG16(0x0400000a) & ~3) | priority;
            break;
        case 1:
            REG16(0x0400000c) = (REG16(0x0400000c) & ~3) | priority;
            break;
        case 2:
            REG16(0x0400000e) = (REG16(0x0400000e) & ~3) | priority;
            break;
        case 3:
            REG16(0x04001008) = (REG16(0x04001008) & ~3) | priority;
            break;
        case 4:
            REG16(0x0400100a) = (REG16(0x0400100a) & ~3) | priority;
            break;
        case 5:
            REG16(0x0400100c) = (REG16(0x0400100c) & ~3) | priority;
            break;
        case 6:
            REG16(0x0400100e) = (REG16(0x0400100e) & ~3) | priority;
            break;
        default:
            break;
    }
}

void func_020028bc(unsigned mode, int a, int b, int c)
{
    switch (mode) {
        case 0:
            *((volatile unsigned short *) 0x0400000A) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400000A) & 0x43) | (a << 14))) | 0x500);
            break;
        case 1:
            *((volatile unsigned short *) 0x0400000C) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400000C) & 0x43) | (a << 14))) | 0x600);
            break;
        case 2:
            *((volatile unsigned short *) 0x0400000E) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400000E) & 0x43) | (a << 14))) | 0x700);
            break;
        case 3:
            *((volatile unsigned short *) 0x04001008) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x04001008) & 0x43) | (a << 14))) | 0xC00);
            break;
        case 4:
            *((volatile unsigned short *) 0x0400100A) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400100A) & 0x43) | (a << 14))) | 0xD00);
            break;
        case 5:
            *((volatile unsigned short *) 0x0400100C) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400100C) & 0x43) | (a << 14))) | 0xE00);
            break;
        case 6:
            *((volatile unsigned short *) 0x0400100E) =
                (c << 2) | (((b << 7) | ((*((volatile unsigned short *) 0x0400100E) & 0x43) | (a << 14))) | 0xF00);
            break;
        default:
            break;
    }
}

void func_0200284c(unsigned int op, int a, int b)
{
    switch (op) {
        case 0:
            func_02001e74(a, b);
            break;
        case 1:
            func_02001e54(a, b);
            break;
        case 2:
            func_02001e34(a, b);
            break;
        case 3:
            func_02001e14(a, b);
            break;
        case 4:
            func_02001df4(a, b);
            break;
        case 5:
            func_02001dd4(a, b);
            break;
        case 6:
            func_02001db8(a, b);
            break;
    }
}
