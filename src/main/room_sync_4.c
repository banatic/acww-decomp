/* room_sync_4: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02052b20 @ 0x02052b20, 0x70 bytes, Thumb
 * func_02052ac8 @ 0x02052ac8, 0x58 bytes, Thumb
 * func_02052a64 @ 0x02052a64, 0x62 bytes, Thumb
 * func_02052a3c @ 0x02052a3c, 0x28 bytes, Thumb
 * func_0205298c @ 0x0205298c, 0xb0 bytes, Thumb
 * func_02052960 @ 0x02052960, 0x2c bytes, Thumb
 */

#include "types.h"

typedef struct {
    unsigned char lo : 6;
    unsigned char f6 : 1;
    unsigned char f7 : 1;
} SomeBits;

typedef union {
    unsigned char byte;
    SomeBits bits;
} Some;

typedef struct {
    u32 c : 1;
    u32 a : 4;
    u32 b : 4;
    u32 flagB : 1;
    u32 flagA : 1;
    u32 h : 16;
} Shared;

typedef struct {
    unsigned int b0 : 4;
    unsigned int b4 : 4;
    unsigned int b8 : 4;
    unsigned int b12 : 1;
    unsigned int b13 : 1;
    unsigned int b14 : 1;
    unsigned int b15 : 16;
} BF;

typedef struct {
    u32 a : 4;
    u32 b : 4;
    u32 s : 16;
} Fields;

typedef struct {
    unsigned short f0 : 6;
    unsigned short f6 : 1;
    unsigned short f7 : 4;
    unsigned short f11 : 4;
} UnkStruct_02052960;

extern unsigned char data_021ebcd4;
extern void *data_020ccf94;
extern int func_02060bf8(void *, int, int);
extern void func_02073820(void *);
extern void func_020737f0(void *, unsigned char *, int);
extern void func_02073770(void *, int, int);
extern void func_020521d8(void *, u32, u32, u8, int, u16 *, int, u32);
extern void func_020523e4(int a0, int a1, int a2, int a3, int a4, int a5, int a6, unsigned short *a7, unsigned char a8);
extern void func_02052118(int a0, int a1, int a2, unsigned short *a3, unsigned char a4);
extern int func_020b65c4(void);
extern int func_ov004_0223cd50(void);
extern int func_ov004_0223cc10(int, int, int, int);
extern int func_ov004_0220d2b8(int);
extern unsigned func_ov004_0223c264(void *);
extern int func_ov004_0223c1ec(void *, int);
extern int func_02052738(int, int, int, int);
extern int func_020526b8(int, int, int, int, int, int, int);
extern unsigned char data_020e54a8;
extern int func_ov004_02211280(char *);

void func_02052b20(Some *p)
{
    int x;
    int y;

    x = p->bits.lo;
    y = p->bits.f6 != 0;

    if (p->bits.f7 == 1) {
        void *o;
        unsigned char tmp;

        func_02060bf8(&data_021ebcd4, x, y);

        tmp = p->byte;
        tmp &= ~0x80;
        o = data_020ccf94;

        func_02073820(o);
        func_020737f0(o, &tmp, 1);
        func_02073770(o, 0x19, 4);
    } else {
        func_02060bf8(&data_021ebcd4, x, y);
    }
}

void func_02052ac8(void *arg0, Shared *data)
{
    u16 h;
    int flagA;
    int flagB;

    h = data->h;
    flagA = data->flagA ? 1 : 0;
    flagB = data->flagB ? 1 : 0;

    func_020521d8(arg0, data->a, data->b, (u8) data->c, flagA, &h, flagB, 0);
}

void func_02052a64(int a0, BF *v)
{
    unsigned short t;
    int f13, f14;
    unsigned char f8, f12;
    unsigned short *p;
    unsigned char zero;

    t = v->b15;
    f13 = v->b13 != 0 ? 1 : 0;
    f14 = v->b14 != 0 ? 1 : 0;
    f8 = v->b8;
    p = &t;
    zero = 0;
    f12 = v->b12;
    func_020523e4(a0, v->b0, v->b4, f12, f13, f14, f8, p, zero);
}

void func_02052a3c(int p0, Fields *src)
{
    unsigned short s;
    s = src->s;
    func_02052118(p0, src->a, src->b, &s, 0);
}

void func_0205298c(int a0, int a1, int a2, int a3, unsigned char a4)
{
    int r;
    int ret;
    unsigned int flag;

    if (func_020b65c4() != a0) {
        return;
    }

    flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag > 0) {
        r = func_ov004_0223cc10(func_ov004_0223cd50(), a1, a2, a3);
        if (r != 0) {
            if (func_ov004_0220d2b8(r + 0x740) == 0) {
                if (func_ov004_0223c264((void *) func_ov004_02211280) >= 4) {
                    ret = func_ov004_0223c1ec((void *) func_ov004_02211280, 0);
                    if (ret != 0) {
                        func_02052738(ret, 0, 0xff, a4);
                    }
                }
                func_020526b8(a1, a2, a3, 1, 0xff, a4, 1);
            } else {
                func_020526b8(a1, a2, a3, 0, 0xff, a4, 1);
            }
        }
    }
}

void func_02052960(UnkStruct_02052960 *p)
{
    func_0205298c((unsigned char) p->f0, p->f7, p->f11, (unsigned char) p->f6, 1);
}
