/* func_0200ea18 @ 0x0200ea18, 0x1a4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0200ea18 {
    u8 pad_00[0x7d4];
    u16 unk_7D4;
    u16 unk_7D6;
    u16 unk_7D8;
    u8 pad_7DA[0x7f0 - 0x7da];
    int unk_7F0;
    u8 pad_7F4[0x81c - 0x7f4];
    int unk_81C;
};

extern void func_02035638(int a);
extern void func_02035684(int a, int b, int c);
extern void func_020110c4(u16 *out, struct UnkStruct_0200ea18 *self);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_0200fc90(struct UnkStruct_0200ea18 *self);
extern u8 data_020e54a8;

void func_0200ea18(struct UnkStruct_0200ea18 *self)
{
    u16 w[2];
    int x;
    int st;

    st = self->unk_81C;
    if (st >= 0xf) {
        return;
    }
    x = 6;
    switch (st) {
        case 11:
            x = 0x23;
        case 10:
            func_02035638(0x39);
            func_02035684(0xc, x, x + 5);
            self->unk_81C = 0xf;
            break;
        case 7: {
            u16 v;
            unsigned int ok;
            v = self->unk_7D4;
            func_02035638(v);
            func_020110c4(w, self);
            if (func_0204bcdc(w) != 0) {
                w[1] = 0xfff1;
                if (func_0204bc64(w) == func_0204bc64(&w[1])) {
                    ok = 1;
                } else {
                    ok = 0;
                }
            } else {
                if (w[0] == 0xfff1) {
                    ok = 1;
                } else {
                    ok = 0;
                }
            }
            if (ok == 0) {
                if (func_0200fc90(self) == 0) {
                    unsigned int t;
                    if (data_020e54a8 == 0) {
                        t = 1;
                    } else {
                        t = 0;
                    }
                    if (t != 0) {
                        x += 0x15;
                    }
                }
            }
            if ((u16) (v + 0xffc4) <= 1) {
                func_02035684(5, x, x + 5);
            } else {
                func_02035684(0xc, x, x + 5);
            }
            self->unk_81C = 0xf;
            break;
        }
        case 5:
        case 8: {
            int k;
            int v;
            x = 0xc;
            k = self->unk_7F0;
            if (k == 0x57) {
                v = self->unk_7D8;
                if (v == 0x3b) {
                    x = 5;
                }
            } else if (k == 0x54) {
                v = self->unk_7D4;
                if (v == 0x3a) {
                    x = 5;
                }
            } else if (k == 0x1c) {
                break;
            } else if (k == 0x19) {
                break;
            } else if (k != 0x5f) {
                break;
            } else {
                v = 0x39;
            }
            func_02035638(v);
            func_02035684(x, 0x14, 0x19);
            if (self->unk_81C != 5) {
                self->unk_81C = 0xf;
            }
            break;
        }
        case 9: {
            int v;
            if (self->unk_7F0 == 0x57) {
                v = self->unk_7D8;
                x += 0x1e;
            } else {
                v = self->unk_7D4;
            }
            func_02035638(v);
            func_02035684(0xc, x, x + 5);
            self->unk_81C = 0xf;
            break;
        }
        case 12:
            func_02035638(0x42);
            func_02035684(0xc, x, 0xb);
            self->unk_81C = 0xf;
            break;
    }
}
