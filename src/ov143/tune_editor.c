/* tune_editor: 10 functions, module ov143
 * mwccarm 1.2/base -O4,s
 * func_ov143_022997d8 @ 0x022997d8, 0x28 bytes, Thumb
 * func_ov143_022997b0 @ 0x022997b0, 0x28 bytes, Thumb
 * func_ov143_02299768 @ 0x02299768, 0x48 bytes, Thumb
 * func_ov143_022996ec @ 0x022996ec, 0x7c bytes, Thumb
 * func_ov143_022996a4 @ 0x022996a4, 0x46 bytes, Thumb
 * func_ov143_02299680 @ 0x02299680, 0x24 bytes, Thumb
 * func_ov143_02299664 @ 0x02299664, 0x1c bytes, Thumb
 * func_ov143_02299650 @ 0x02299650, 0x12 bytes, Thumb
 * func_ov143_02299640 @ 0x02299640, 0xe bytes, Thumb
 * func_ov143_02299630 @ 0x02299630, 0xe bytes, Thumb
 */

typedef struct {
    unsigned char v[16];
} Blk16;

struct UnkStruct_02299768 {
    unsigned int value : 10;
};

struct UnkStruct_022996ec {
    unsigned int low10 : 10;
    unsigned int high22 : 22;
};

typedef struct {
    char pad_00[0xa0];
    unsigned char *ptr;
} UnkStruct_022996a4;

extern Blk16 data_ov143_0229afb0;
extern Blk16 data_ov143_0229afd0;
extern int func_ov143_02299a64(int);
extern int func_0207094c(int, int);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);
extern struct UnkStruct_02299768 *data_ov143_0229b178[];
extern struct UnkStruct_022996ec data_ov143_0229afc0[];
extern void func_02001a7c(void);
extern void func_02001a1c(int);
extern void func_ov002_0220a6b8(void *);
extern void func_02001a5c(void);
extern void func_ov002_0220a690(void *);

unsigned char func_ov143_022997d8(int unused, int index)
{
    Blk16 buf;

    buf = data_ov143_0229afb0;
    return buf.v[index];
}

unsigned char func_ov143_022997b0(int unused, int index)
{
    Blk16 buf;

    buf = data_ov143_0229afd0;
    return buf.v[index];
}

void func_ov143_02299768(int a0, int a1, int a2)
{
    struct UnkStruct_02299768 *p;
    int ret;
    p = data_ov143_0229b178[a2];
    ret = func_ov143_02299a64(a0);
    func_0207094c(ret, a1);
    func_02070adc(ret, 8, p[1].value, 3, 15, 0, 0);
    func_02070a04(ret, 1, 0);
}

void func_ov143_022996ec(int param)
{
    int i;
    unsigned char cur = 0xc7;
    unsigned char reset = 0xc3;
    i = 0;
    while (i < 13) {
        func_ov143_02299768(param, cur, i);
        cur = (unsigned char) (cur + 1);
        if (cur > 0xc9) {
            cur = reset;
        }
        i++;
    }

    func_ov143_02299768(param, 0xca, 0xd);
    func_ov143_02299768(param, 0xcb, 0xe);
    {
        int handle = func_ov143_02299a64(param);
        func_0207094c(handle, 0x8d);
        func_02070adc(handle, 8, data_ov143_0229afc0[1].low10, 8, 15, 0 & 0xFFFFFFFFFFFFFFFF, 0);
        func_02070a04(handle, 1, 0);
    }
}

void func_ov143_022996a4(UnkStruct_022996a4 *a, int *dst, int idx)
{
    int d;
    int x = 26;
    int y = 63;

    d = (int) func_ov143_022997d8((int) a, (unsigned char) a->ptr[idx]);
    if (idx < 8) {
        x += 24 * idx;
        y -= 2 * d;
    } else {
        x += 24 * (idx - 8) + 16;
        y += 56 - 2 * d;
    }
    dst[0] = x;
    dst[1] = y;
}

void func_ov143_02299680(void *p)
{
    func_02001a7c();
    func_02001a1c(~5);
    func_ov002_0220a6b8((char *) p + 0x110);
}

void func_ov143_02299664(void *p)
{
    func_02001a5c();
    func_ov002_0220a690((char *) p + 0x110);
}

int func_ov143_02299650(unsigned short *base, unsigned short mask)
{
    if ((base[0x4c] & mask) == 0) {
        return 0;
    }
    return 1;
}

void func_ov143_02299640(unsigned short *p, unsigned short v)
{
    p[0x4C] = p[0x4C] | v;
}

void func_ov143_02299630(unsigned short *p, unsigned short mask)
{
    p[0x4c] = p[0x4c] & ~mask;
}
