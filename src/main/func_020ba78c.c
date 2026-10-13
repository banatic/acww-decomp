/* func_020ba78c @ 0x020ba78c, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O1,s
 */

#include "types.h"

struct UnkStruct_020ba78c {
    int pad_00[8];
    int unk_20;
    int pad_24;
    int unk_28;
    int pad_2C;
    int unk_30;
    int pad_34[17];
    int unk_78;
};
struct UnkStruct_020ba78c_2 {
    int pad_00[3];
    int unk_0C;
};

extern struct UnkStruct_020ba78c data_021f8ab0;
extern struct UnkStruct_020ba78c_2 data_021f8b30;
extern int data_021f8ad4;
extern u8 *data_021f8b34;
extern void *data_021f8b38;
extern int data_021f75b0;
extern u8 data_020d22bc[];

extern int func_020bb66c(void *, int, int);
extern int func_020bb608(void *, void *, void *, int, int);
extern int func_02002b40(void *, int, int, int);

int func_020ba78c(int idx)
{
    int ok;
    int t;
    int v;
    int tgt;
    u8 *p;
    int mode;
    int cur;
    int f28;
    int dir;
    int n;
    int a2;

    ok = 0;
    if (data_021f8ab0.unk_20 != 0 && data_021f8ab0.unk_30 != 2) {
        mode = data_021f8ab0.unk_30;
        v = data_021f8ab0.unk_78;
        cur = data_021f8ad4;
        f28 = data_021f8ab0.unk_28;
        if (f28 == cur) {
            if (v >= 0) {
                v = 0x20 - v;
            } else if (v == 0 && (data_021f8b30.unk_0C == 3 || data_021f8b30.unk_0C == 4)) {
                v = 0x20 - v;
            }
        }
        if (v <= 0) {
            ok = 1;
        } else {
            t = data_020d22bc[idx];
            if (mode == 0) {
                tgt = cur + 1;
                dir = 1;
            } else {
                tgt = cur - 1;
                dir = 2;
            }
            if ((data_021f8b30.unk_0C == 3 || data_021f8b30.unk_0C == 4) && f28 == cur) {
                tgt = cur;
            }
            if (func_020bb66c(&data_021f75b0, tgt, t) != 0) {
                if (func_020bb608(&data_021f75b0, &data_021f8b34, &data_021f8b38, dir, tgt) != 0) {
                    p = data_021f8b34;
                    if (tgt == data_021f8ad4) {
                        a2 = v * 32;
                        n = (0x20 - v) * 32;
                        p = p + n;
                    } else {
                        a2 = v * 32;
                        n = 0;
                    }
                    if (func_02002b40(p, t, a2, n) != 0) {
                        ok = 1;
                    }
                }
            }
        }
    } else {
        ok = 1;
    }
    return ok;
}
