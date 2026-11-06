/* star_scope: 10 functions, module ov127
 * mwccarm 1.2/base -O4,s
 * func_ov127_0229a0ec @ 0x0229a0ec, 0x10 bytes, Thumb
 * func_ov127_0229a0e8 @ 0x0229a0e8, 0x2 bytes, Thumb
 * func_ov127_0229a0bc @ 0x0229a0bc, 0x2c bytes, Thumb
 * func_ov127_0229a04c @ 0x0229a04c, 0x70 bytes, Thumb
 * func_ov127_02299fd4 @ 0x02299fd4, 0x78 bytes, Thumb
 * func_ov127_02299f90 @ 0x02299f90, 0x44 bytes, Thumb
 * func_ov127_02299e64 @ 0x02299e64, 0x12c bytes, Thumb
 * func_ov127_02299e5c @ 0x02299e5c, 0x8 bytes, Thumb
 * func_ov127_02299de8 @ 0x02299de8, 0x74 bytes, Thumb
 * func_ov127_02299dc0 @ 0x02299dc0, 0x28 bytes, Thumb
 */

#include "types.h"

typedef struct {
    char pad_00[0x24];
    char unk_24;
    char pad_25[0x1024 - 0x25];
    char unk_1024;
    char pad_1025[0x2824 - 0x1025];
    s16 unk_2824;
    s16 unk_2826;
    char pad_2828[0x282e - 0x2828];
    s16 unk_282E;
    char pad_2830[2];
    u8 unk_2832;
} UnkStruct_02299e64;

typedef struct {
    int a;
    int b;
} UnkStruct_02299de8;

extern int func_020b9cfc(int);
extern void func_020028bc(int a, int b, int c, int d);
extern void *data_ov127_0229b6ac;
extern int data_021fbe94;
extern int func_02002c6c(void *table, int deref, int b, int c, int d, int e);
extern void *data_ov127_0229b6c0;
extern int func_02064af4(void *table, void *dst, int size);
extern void func_020b0fa0(void *p);
extern int func_02002b40(void *p, int a, int b, int c);
extern const int data_ov127_0229b664[];
extern const int data_ov127_0229b67c[];
extern const int data_ov127_0229b694[];
extern int func_02002d14(const int *data, int a, unsigned char b, int c, int d, int e);
extern const char data_ov127_0229b634[];
extern const char data_ov127_0229b64c[];
extern int func_ov127_02299878(UnkStruct_02299e64 *self, int a);
extern void func_ov127_022998b4(UnkStruct_02299e64 *self);
extern void func_0200284c(int a, int b, int c);
extern void func_ov127_02299858(UnkStruct_02299e64 *self, int a);
extern void func_ov127_02299868(UnkStruct_02299e64 *self, int a);
extern void MI_CpuCopy8(void *src, void *dst, int n);
extern int func_020b9bbc(UnkStruct_02299e64 *self, void *p, int a, int b, int c);
extern void func_020b9ccc(void *argument0);
extern int data_ov127_0229b5f4[4];
extern int data_ov127_0229b604[4];
extern UnkStruct_02299de8 data_ov127_0229b614[4];
extern int func_020896b8(int, UnkStruct_02299de8 *, int, int, int, int, int);
extern const char data_ov127_0229b5ec[];

int func_ov127_0229a0ec(int a)
{
    func_020b9cfc(a);
    return a;
}

void func_ov127_0229a0e8(void *object) {}

void func_ov127_0229a0bc(unsigned short *param0)
{
    param0[0x1418] = 0;
    param0[0x1412] = 0;
    param0[0x1413] = 0;
    param0[0x1417] = 0;
    param0[0x1414] = 0;
}

void func_ov127_0229a04c(unsigned char *self, unsigned char param1)
{
    self[0x2832] = param1;
    func_020028bc(self[0x2832], 1, 0, 0);
    func_02002c6c(&data_ov127_0229b6ac, data_021fbe94, self[0x2832], 0x10, 0x10, 0x1f);
    func_02064af4(&data_ov127_0229b6c0, self + 0x24, 0x1000);
    func_020b0fa0(self + 0x24);
    func_02002b40(self + 0x24, self[0x2832], 0x1000, 0);
}

void func_ov127_02299fd4(unsigned char *self, unsigned char val, int mode)
{
    int g = data_021fbe94;
    self[0x2833] = val;
    func_02002d14(data_ov127_0229b664, g, self[0x2833], 4, 8, 0xb);
    func_02002c6c((void *) data_ov127_0229b67c, g, (int) self[0x2833], 0x20, 0x20, 0xbf);
    func_02064af4((void *) data_ov127_0229b694, self + 0x2024, 0x800);
    func_02002b40(self + 0x2024, (int) self[0x2833], 0x800, 0);
}

void func_ov127_02299f90(void *receiver)
{
    void *p = (*(void **) &data_021fbe94);
    func_02002d14((const int *) data_ov127_0229b634, (int) p, (unsigned char) 8, 5, 5, 9);
    func_02002c6c((void *) data_ov127_0229b64c, (int) p, 8, 0xc0, 0xc0, 0x13f);
}

void func_ov127_02299e64(UnkStruct_02299e64 *self)
{
    int v;
    int t;
    int n;
    u16 *p;
    int j;
    u16 *q;
    int k;
    int i;

    if (func_ov127_02299878(self, 4) != 0) {
        func_ov127_022998b4(self);
    }
    if (func_ov127_02299878(self, 1) != 0) {
        func_0200284c(self->unk_2832, self->unk_2824, self->unk_2826);
        func_ov127_02299858(self, 1);
        t = 0;
        v = self->unk_2826;
        if (v < 0) {
            t = ((v - 7) << 13) >> 16;
        } else if (v >= 0x40) {
            t = ((v - 0x39) << 13) >> 16;
        }
        if (t != self->unk_282E) {
            self->unk_282E = t;
            func_ov127_02299868(self, 2);
        }
    }
    if (func_ov127_02299878(self, 2) != 0) {
        MI_CpuCopy8(&self->unk_24, &self->unk_1024, 0x1000);
        n = self->unk_282E;
        if (n > 0) {
            p = (u16 *) &self->unk_1024;
            q = (u16 *) ((char *) p + 0x800);
            j = 0;
            for (i = 0; i < self->unk_282E; i++) {
                for (k = j; k < 0x20; k++) {
                    *p = 0x4010;
                    *q = 0x4010;
                    p++;
                    q++;
                }
            }
        } else if (n < 0) {
            p = (u16 *) ((char *) &self->unk_1024 + (n + 0x20) * 0x40);
            q = (u16 *) ((char *) p + 0x800);
            j = 0;
            for (i = 0; i > self->unk_282E; i--) {
                for (k = j; k < 0x20; k++) {
                    *p = 0x4010;
                    *q = 0x4010;
                    p++;
                    q++;
                }
            }
        }
        func_020b9bbc(self, &self->unk_1024, self->unk_2832, 0x1000, 0);
        func_ov127_02299858(self, 2);
    }
}

void func_ov127_02299e5c(void *argument0)
{
    func_020b9ccc(argument0);
}

#pragma opt_loop_invariants off
void func_ov127_02299de8(unsigned char *obj, int a2, int a3)
{
    int local = 0;
    int i;
    int fifth;

    for (i = 0; i < 4; i++) {
        if (i == obj[0x2834]) {
            fifth = 7;
        } else {
            fifth = a3;
        }

        func_020896b8(1, &data_ov127_0229b614[i], data_ov127_0229b5f4[i] * (a2 >> 2) + 0x80,
                      data_ov127_0229b604[i] * (a2 >> 2) + 0x60, fifth, 1, local);
    }
    obj[0x2834] = 4;
}

void func_ov127_02299dc0(int unused, void *p)
{
    func_020896b8(1, (UnkStruct_02299de8 *) data_ov127_0229b5ec, 0x80, (int) ((char *) p + 0x60), -1, 1, 0);
}
