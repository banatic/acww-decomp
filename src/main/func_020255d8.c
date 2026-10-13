/* func_020255d8 @ 0x020255d8, 0x160 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int n;
    unsigned char b;
} UnkStruct_020255d8;
typedef void (*Fn)(void *self, UnkStruct_020255d8 *out);

typedef struct {
    int fn;
    int adj;
} Pmf;

typedef struct {
    char pad_00[0x40];
    int unk_40;
    char pad_44[0xb0 - 0x44];
    Pmf pmf;
    char pad_B8[0x164 - 0xb8];
    int unk_164;
} UnkStruct_020255d8_2;

typedef struct {
    int a;
    int b;
} Pair;

extern Pair data_020d8f38;
extern Pair data_020d8fd0;

extern void *func_0202d9c4(UnkStruct_020255d8_2 *self);
extern int func_0209bc40(void *a);
extern u16 *func_0209b8c4(int a);
extern void func_0202da88(UnkStruct_020255d8_2 *self, void *tbl);
extern void func_0206844c(int a, void *b, int c);
extern int func_0209bb70(void *a);
extern int func_02029a18(int a);
extern void func_02015800(UnkStruct_020255d8_2 *self, int b, int c, int d);
extern void func_02015828(UnkStruct_020255d8_2 *self, int b);
extern void func_0202dbf0(UnkStruct_020255d8_2 *self, Pair p);

extern unsigned char data_021c2d94[];

void func_020255d8(UnkStruct_020255d8_2 *self)
{
    UnkStruct_020255d8 out;

    switch (func_0209bc40(func_0202d9c4(self))) {
        case 0: {
            unsigned char arg;
            int ok;
            u16 h;
            u16 *p;
            p = func_0209b8c4(self->unk_164);
            ok = 0;
            h = *p;
            if (h >= 0x12b0 && h <= 0x12e7) {
                ok = 1;
            }
            if (ok != 0) {
                func_0202da88(self, (void *) data_021c2d94);
                if (((volatile Pmf *) &self->pmf)->fn != 0) {
                    volatile Pmf *pm;
                    int adj;
                    char *t;
                    Fn fp;

                    pm = (volatile Pmf *) &self->pmf;
                    adj = pm->adj;
                    t = (char *) self + (adj >> 1);
                    if (adj & 1) {
                        fp = (Fn) * (int *) (*(char **) t + pm->fn);
                    } else {
                        fp = (Fn) pm->fn;
                    }
                    fp(t, &out);
                }
                arg = out.b;
                func_0206844c(self->unk_40, &arg, out.n);
            } else {
                func_02015800(self, func_02029a18(func_0209bb70(func_0202d9c4(self))), 0xd, 1);
                func_02015828(self, 0);
                func_0202dbf0(self, data_020d8f38);
            }
            break;
        }
        case 1: {
            unsigned char arg2;
            int ok;
            u16 h;
            u16 *p;
            p = func_0209b8c4(self->unk_164);
            ok = 0;
            h = *p;
            if (h >= 0x12e8 && h <= 0x131f) {
                ok = 1;
            }
            if (ok != 0) {
                func_0202da88(self, (void *) data_021c2d94);
                if (((volatile Pmf *) &self->pmf)->fn != 0) {
                    volatile Pmf *pm;
                    int adj;
                    char *t;
                    Fn fp;

                    pm = (volatile Pmf *) &self->pmf;
                    adj = pm->adj;
                    t = (char *) self + (adj >> 1);
                    if (adj & 1) {
                        fp = (Fn) * (int *) (*(char **) t + pm->fn);
                    } else {
                        fp = (Fn) pm->fn;
                    }
                    fp(t, &out);
                }
                arg2 = out.b;
                func_0206844c(self->unk_40, &arg2, out.n);
            } else {
                func_02015800(self, func_02029a18(func_0209bb70(func_0202d9c4(self))), 0xd, 1);
                func_02015828(self, 0);
                func_0202dbf0(self, data_020d8fd0);
            }
            break;
        }
    }
}
