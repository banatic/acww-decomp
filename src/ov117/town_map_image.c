/* town_map_image: 17 functions, module ov117
 * mwccarm 1.2/base -O4,s
 * func_ov117_02299ca4 @ 0x02299ca4, 0x2c bytes, Thumb
 * func_ov117_02299c9c @ 0x02299c9c, 0x8 bytes, Thumb
 * func_ov117_02299c68 @ 0x02299c68, 0x32 bytes, Thumb
 * func_ov117_02299c50 @ 0x02299c50, 0x18 bytes, Thumb
 * func_ov117_02299c4c @ 0x02299c4c, 0x2 bytes, Thumb
 * func_ov117_02299b40 @ 0x02299b40, 0x10c bytes, Thumb
 * func_ov117_02299b08 @ 0x02299b08, 0x38 bytes, Thumb
 * func_ov117_02299adc @ 0x02299adc, 0x2a bytes, Thumb
 * func_ov117_02299ab8 @ 0x02299ab8, 0x24 bytes, Thumb
 * func_ov117_02299aa4 @ 0x02299aa4, 0x12 bytes, Thumb
 * func_ov117_02299a94 @ 0x02299a94, 0x10 bytes, Thumb
 * func_ov117_02299a88 @ 0x02299a88, 0xc bytes, Thumb
 * func_ov117_02299a48 @ 0x02299a48, 0x40 bytes, Thumb
 * func_ov117_02299a18 @ 0x02299a18, 0x30 bytes, Thumb
 * func_ov117_022999fc @ 0x022999fc, 0x1c bytes, Thumb
 * func_ov117_022999e0 @ 0x022999e0, 0x1c bytes, Thumb
 * func_ov117_022999a0 @ 0x022999a0, 0x40 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02299ca4 {
    short x;
    short y;
    unsigned char z;
};

struct tile {
    char data[512];
};

extern void func_ov117_0229a10c(void *argument0);
extern void func_ov117_0229a194(void *);
extern void func_ov117_02299d9c(void *);
extern void func_ov117_02299ee8(void *);
extern void func_ov117_0229a034(void *);
extern void func_ov117_02299f8c(void *);
extern void func_ov117_02299e44(void *);
extern void func_ov117_02299cd0(void *);
extern void func_02030e4c(int);
extern int func_0203194c(u8 *tile, int x, int y);
extern void *func_ov117_0229a2f0(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void *data_020da1a8;
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);
extern void *data_ov117_0229a320;
extern void *func_020e98b4(int);
extern void func_020e9898(int);

struct tile *func_ov117_02299aa4(struct tile *base, unsigned int a, unsigned int b);
void func_ov117_02299a18(void);
void func_ov117_022999fc(int param);
void func_ov117_022999e0(void *p);
void func_ov117_022999a0(int p0, int p1);

void func_ov117_02299ca4(struct UnkStruct_02299ca4 *src, struct UnkStruct_02299ca4 *dst)
{
    unsigned int i;
    for (i = 0; i < 17; i++) {
        dst[i].x = src[i].x;
        dst[i].y = src[i].y;
        dst[i].z = src[i].z;
    }
}

void func_ov117_02299c9c(void *argument0)
{
    func_ov117_0229a10c(argument0);
}

void func_ov117_02299c68(void *p)
{
    func_ov117_0229a194(p);
    func_ov117_02299d9c(p);
    func_ov117_02299ee8(p);
    func_ov117_0229a034(p);
    func_ov117_02299f8c(p);
    func_ov117_02299e44(p);
    func_ov117_02299cd0(p);
}

void func_ov117_02299c50(unsigned char *arr)
{
    unsigned int i;
    unsigned char fill;
    i = 0;
    fill = i;
    goto test;
loop:
    arr[i] = fill;
    i++;
test:
    if (i < 0x200) {
        goto loop;
    }
}

void func_ov117_02299c4c(void *element) {}

void func_ov117_02299b40(u8 *dst, int cx, int cy)
{
    unsigned int ox, oy;
    unsigned int n;
    u8 v;
    unsigned int ys, xs, yodd;
    int oyy;
    unsigned int ty, tx, py, px;
    unsigned int yy, xx;
    int ex, ey;
    u8 tile[4];

    func_02030e4c(1);
    ox = cx * 16 + 16;
    oy = cy * 16 + 16;
    n = 0;
    for (ty = 0; ty < 4; ty++) {
        tx = 0;
        ys = ty * 8;
        for (; tx < 4; tx++) {
            py = 0;
            xs = tx * 8;
            for (; py < 8; py++) {
                px = 0;
                yy = ys + py;
                yodd = yy & 1;
                oyy = oy + (yy >> 1);
                for (; px < 8; px++) {
                    xx = xs + px;
                    ex = (xx & 1) == 0 ? 1 : 0;
                    ey = yodd == 0 ? 1 : 0;
                    v = 0;
                    if (func_0203194c(tile, ox + (xx >> 1), oyy)) {
                        if (ex) {
                            v = (ey ? tile[0] : tile[2]) & 0xf;
                        } else {
                            v = (u8) ((u8) ((ey ? tile[1] : tile[3]) & 0xf) << 4);
                        }
                    }
                    dst[n++ >> 1] |= v;
                }
            }
        }
    }
    func_02030e4c(0);
}

void *func_ov117_02299b08(void *self)
{
    __cxa_vec_ctor(self, 16, 512, (void (*)(void *)) func_ov117_02299c50, func_ov117_02299c4c);
    func_ov117_0229a2f0((char *) self + 8192);
    return self;
}

void func_ov117_02299adc(int a, int b)
{
    unsigned int i = 0;
    unsigned int mask = b & 3;
    for (; i < 4; i++) {
        func_ov117_02299b40((u8 *) ((void *) func_ov117_02299aa4((struct tile *) ((void *) a), i, mask)), i, mask);
    }
}

void func_ov117_02299ab8(unsigned int r0, int r1)
{
    if (r1 == 0) {
        func_ov117_02299c9c((void *) (r0 + 0x2000));
    } else {
        func_ov117_02299c68((void *) (r0 + 0x2000));
    }
}

struct tile *func_ov117_02299aa4(struct tile *base, unsigned int a, unsigned int b)
{
    if (a >= 4 || b >= 4) {
        return base;
    }
    return &base[a + b * 4];
}

void func_ov117_02299a94(int a, int b)
{
    MI_CpuCopy8((const void *) a, (void *) b, 0x2000);
}

int func_ov117_02299a88(int a)
{
    return a + 0x2000;
}

void func_ov117_02299a48(int a, int b)
{
    int r5 = a;
    int r4 = b;
    func_ov117_02299a18();
    func_ov117_022999fc(0);
    func_ov117_022999fc(1);
    func_ov117_022999fc(2);
    func_ov117_022999fc(3);
    func_ov117_022999e0(0);
    func_ov117_022999e0((void *) 1);
    func_ov117_022999a0(r5, r4);
}

void func_ov117_02299a18(void)
{
    if (data_ov117_0229a320 == 0) {
        data_ov117_0229a320 = func_020e98b4(0x2066);
        if (data_ov117_0229a320 != 0) {
            if (data_ov117_0229a320 != 0) {
                func_ov117_02299b08((void *) (data_ov117_0229a320));
            }
        }
    }
}

void func_ov117_022999fc(int param)
{
    if ((*(int *) &data_ov117_0229a320)) {
        func_ov117_02299adc((*(int *) &data_ov117_0229a320), param);
    }
}

void func_ov117_022999e0(void *p)
{
    if ((*(int *) &data_ov117_0229a320)) {
        func_ov117_02299ab8((unsigned int) ((*(int *) &data_ov117_0229a320)), (int) p);
    }
}

void func_ov117_022999a0(int p0, int p1)
{
    if ((*(int *) &data_ov117_0229a320) != 0) {
        func_ov117_02299a94((*(int *) &data_ov117_0229a320), p0);
        if (p1 != 0) {
            func_ov117_02299ca4((struct UnkStruct_02299ca4 *) (func_ov117_02299a88((*(int *) &data_ov117_0229a320))), (struct UnkStruct_02299ca4 *) p1);
        }
        func_020e9898((*(int *) &data_ov117_0229a320));
        (*(int *) &data_ov117_0229a320) = 0;
    }
}
