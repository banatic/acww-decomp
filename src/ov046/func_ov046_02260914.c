/* func_ov046_02260914 @ 0x02260914, 0x194 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 kind;
    u8 pad_01[3];
    int unk_04;
    int unk_08;
} Msg;

typedef struct {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x21];
    void *unk_40;
    char pad_44[0xc0 - 0x44];
    int unk_C0;
    u8 unk_C4;
    u8 unk_C5;
    u8 unk_C6;
    char pad_C7[1];
    int unk_C8[5];
    int unk_DC;
} Obj_ov046_0226204c;

extern char data_ov046_02262420[]; // data_02262420

extern void *func_020b1954(char *b);
extern int func_020b1394(char *b, int a);
extern void func_02068404(void *h, int a, char *b);
extern void func_020b12e0(int *d, int a);
extern void func_02015ed0(Obj_ov046_0226204c *self, int a, int b);
extern void func_02015ea0(Obj_ov046_0226204c *self, int a, int b);
extern void func_02015fb0(Obj_ov046_0226204c *self, int a, int b, int c, int d, int e);
extern int func_020683e4(void *h, int a, u8 *m, char *t);
extern void func_020157b0(Obj_ov046_0226204c *self, int a, int b, int c);
extern int func_02015828(Obj_ov046_0226204c *self, int a);
extern void func_ov046_02261508(Obj_ov046_0226204c *self, int a); // func_02261508
extern void *func_020b193c(char *b);
extern int func_ov046_022610fc(Obj_ov046_0226204c *self); // func_022610fc
extern int func_020b1558(void);

void func_ov046_02260914(Obj_ov046_0226204c *self, int idx)
{
    Msg m;
    char buf[0x24];
    void *h;
    int mode;
    int v;
    int n;
    int k;

    h = self->unk_40;
    self->unk_C0 = self->unk_C8[idx];
    if (self->unk_C0 < 0) {
        goto neg;
    }
    func_020b1954(buf);
    func_020b1394(buf, self->unk_C0);
    func_02068404(self->unk_40, 6, buf);
    mode = self->unk_C6;
    if (mode == 0) {
        self->unk_DC = 0x19;
        self->unk_C4 = 0;
    } else if (mode == 1) {
        m.unk_04 = 0;
        m.unk_08 = 0;
        func_020b12e0(&m.unk_04, self->unk_C0);
        func_02015ed0(self, ((u8 *) &m)[8], 2);
        func_02015ea0(self, ((u8 *) &m)[7], 3);
        func_02015fb0(self, ((u8 *) &m)[5], 5, 2, 0, 0);
        v = ((u8 *) &m)[6];
        n = 0x19;
        if (v > 0xc) {
            n = 0x1a;
            v = v - 0xc;
        }
        m.kind = (u8) n;
        func_020683e4(h, 8, (u8 *) &m, data_ov046_02262420);
        func_02015fb0(self, v, 4, 2, 0, 0);
        self->unk_DC = 0x17;
    } else if (mode == 2) {
        func_020157b0(self, 0x2e, (u8) self->unk_C0, 0);
        func_02015828(self, 3);
        func_ov046_02261508(self, 3);
    }
    self->unk_C6 = 0;
    func_020b193c(buf);
    return;
neg:
    if (self->unk_C5 == 0) {
        self->unk_DC = func_ov046_022610fc(self);
        if ((u8) (self->unk_C6 + 0xff) <= 1) {
            if (func_020b1558() < 0x10) {
                if (self->unk_C6 == 1) {
                    self->unk_DC = 0x16;
                } else {
                    self->unk_DC = 0x1d;
                }
            }
        }
        self->unk_C6 = 0;
        return;
    }
    k = self->unk_1E;
    if (k == 0x15) {
        goto set3f;
    }
    if (k == 0x1e) {
        goto set3f;
    }
    if (k == 0x1f) {
    set3f:
        self->unk_DC = 0x3f;
        return;
    }
    if (k == 0x3f) {
        self->unk_DC = 0x40;
        return;
    }
    if (k == 0x40) {
        self->unk_DC = 0x41;
    }
    return;
}
