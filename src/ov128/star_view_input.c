/* star_view_input: 6 functions, module ov128
 * mwccarm 1.2/base -O4,s
 * func_ov128_0229b9f0 @ 0x0229b9f0, 0x64 bytes, Thumb
 * func_ov128_0229b90c @ 0x0229b90c, 0xe4 bytes, Thumb
 * func_ov128_0229b8d4 @ 0x0229b8d4, 0x38 bytes, Thumb
 * func_ov128_0229b8bc @ 0x0229b8bc, 0x18 bytes, Thumb
 * func_ov128_0229b88c @ 0x0229b88c, 0x30 bytes, Thumb
 * func_ov128_0229b804 @ 0x0229b804, 0x88 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x2cdc];
    char unk_2CDC;
    char pad_2CDD[0x2d60 - 0x2cdd];
    int unk_2D60;
    int unk_2D64;
    char pad_2D68[0x2d6e - 0x2d68];
    u8 unk_2D6E;
    char pad_2D6F;
    u8 unk_2D70;
} UnkStruct_0229b90c;

typedef struct {
    char pad_00[0x2d5c];
    int a;
    int b;
} UnkStruct_0229b88c;

typedef struct {
    u8 pad_00[0x2d5c];
    u32 word; // 0x2d5c
    u8 pad_2D60[0x2d6d - 0x2d60];
    u8 b6d; // 0x2d6d
    u8 b6e; // 0x2d6e
    u8 b6f; // 0x2d6f
} UnkStruct_0229b804;

extern void func_02088df8(int a, char *b, void *c, void *d, int e, int f, int g, int h, int i, int j, int k, int l);
extern int data_ov128_0229ca00[];
extern int data_ov128_0229c890[];
extern void *func_020b1530(int a);
extern void func_02051bf8(u16 *buf, int n);
extern void func_02051c08(void *p, u16 *buf, int n);
extern int func_02051ca8(void *p, int n);
extern void func_020708e4(void *p, u16 *buf, int n);
extern int func_0207096c(void *p);
extern void func_02070adc(void *p, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *p, int a, int b);

void func_ov128_0229b9f0(unsigned char *self)
{
    unsigned char idx1;
    unsigned char idx2;
    char *b;
    char *d;

    if (self[0x2d6e] == 0) {
        return;
    }

    idx1 = self[0x2d70];
    b = (char *) data_ov128_0229ca00[idx1 - 2];
    idx2 = self[0x2d6d];
    d = (char *) data_ov128_0229c890[idx2] + 0x60;

    func_02088df8(1, b, (void *) 0x80, d, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
}

void func_ov128_0229b90c(UnkStruct_0229b90c *self)
{
    u16 buf[10];
    void *h;
    int n;

    if (self->unk_2D60 == -1) {
        self->unk_2D6E = 0;
    } else {
        self->unk_2D6E = 1;
        if (self->unk_2D60 != self->unk_2D64) {
            h = func_020b1530(self->unk_2D60);
            func_02051bf8(buf, 8);
            func_02051c08((char *) h + 0x1e, buf, 6);
            n = func_02051ca8((char *) h + 0x1e, 6);
            func_02051c08((char *) h + 0x1e, buf, n);
            buf[n] = 0xc790;
            buf[n + 1] = 0xb9ac;
            func_020708e4(&self->unk_2CDC, buf, n + 2);
            self->unk_2D70 = (func_0207096c(&self->unk_2CDC) + 7) >> 3;
            if (self->unk_2D70 < 2) {
                self->unk_2D70 = 2;
            }
            func_02070adc(&self->unk_2CDC, 8, 0xc6, self->unk_2D70, 0xf, 0, 0);
            func_02070a04(&self->unk_2CDC, 1, 0);
            self->unk_2D64 = self->unk_2D60;
        }
    }
}

void func_ov128_0229b8d4(void *r0)
{
    unsigned int r2;
    unsigned int r1;
    unsigned char r2b;

    r2 = *(unsigned int *) ((char *) r0 + 0x2d60);
    r1 = 0xffffffff;
    if (r2 != r1) {
        r1 = *(unsigned int *) ((char *) r0 + 0x2d64);
        if (r2 == r1) {
            func_ov128_0229b90c((UnkStruct_0229b90c *) r0);
            return;
        }
    }
    r2b = 3;
    *(unsigned char *) ((char *) r0 + 0x2d6e) = r2b;
}

void func_ov128_0229b8bc(void *r0)
{
    *(int *) ((char *) r0 + 0x2d60) = -1;
    *(unsigned char *) ((char *) r0 + 0x2d6e) = 3;
}

void func_ov128_0229b88c(UnkStruct_0229b88c *p)
{
    if (p->a != -1 && p->b != p->a) {
        p->b = p->a;
        func_ov128_0229b8d4((void *) p);
    }
}

void func_ov128_0229b804(UnkStruct_0229b804 *self)
{
    switch (self->b6e) {
        case 1:
            if (self->b6d < 3) {
                self->b6d++;
            } else {
                self->b6e = 2;
                self->b6f = 20;
            }
            break;
        case 2:
            if (self->word == -1) {
                if (self->b6f != 0) {
                    self->b6f--;
                } else {
                    func_ov128_0229b8bc((void *) self);
                }
            } else {
                self->b6f = 20;
            }
            break;
        case 3:
            if (self->b6d != 0) {
                self->b6d--;
            } else {
                func_ov128_0229b90c((UnkStruct_0229b90c *) self);
            }
            break;
        default:
            break;
    }
}
