/* func_ov086_02278cf0 @ 0x02278cf0, 0x17c bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_020984e8(void);
extern int func_02099640(int);
extern int func_02099e9c(u16 *);
extern void func_0209df64(void *);
extern void func_0209e474(void *);
extern int func_0209dcac(void);
extern int func_020644cc(int);
extern int func_0208602c(void);
extern int func_02086108(int, int);
extern int func_02099fe8(void);

extern u8 data_ov086_02279448[];
extern u8 data_ov086_02279438[];

typedef struct {
    u8 pad_00[0xb4];
    int unk_B4;
} UnkStruct_02278cf0;

typedef struct {
    void *ptr;
    u8 byte;
} UnkStruct_02278cf0_2;

typedef struct {
    u16 a;
    u8 b[6];
    u32 c;
    u32 d;
} Locals;

void func_ov086_02278cf0(UnkStruct_02278cf0 *self, UnkStruct_02278cf0_2 *out)
{
    Locals loc;
    unsigned int flag;

    func_02099640((int) func_020984e8());

    out->ptr = data_ov086_02279448;
    if (self->unk_B4 == -1) {
        loc.a = 0x37e0;
        self->unk_B4 = func_02099e9c(&loc.a);
        if (self->unk_B4 >= 0) {
            out->ptr = data_ov086_02279438;
            out->byte = 0;
            return;
        }
    }

    func_0209df64(loc.b);
    loc.c = 0;
    loc.d = 0;
    func_0209e474(&loc.c);
    flag = 0;

    if (loc.b[1] == 12) {
        if (func_0209dcac() == 0) {
            out->byte = func_020644cc(3);
        } else if (func_0209dcac() == 1) {
            out->byte = func_020644cc(3);
            if (out->byte != 0) {
                out->byte += 2;
            }
        } else if (((u8 *) &loc.c)[2] < 23) {
            out->byte = func_020644cc(3);
            if (out->byte != 0) {
                out->byte += 4;
            }
        } else if (((u8 *) &loc.c)[2] == 23 && ((u8 *) &loc.c)[1] < 30) {
            out->byte = func_020644cc(3);
            if (out->byte != 0) {
                out->byte += 6;
            }
        } else if (((u8 *) &loc.c)[2] == 23 && ((u8 *) &loc.c)[1] < 55) {
            out->byte = func_020644cc(3) + 9;
        } else if (((u8 *) &loc.c)[2] == 23 && ((u8 *) &loc.c)[1] < 59) {
            out->byte = func_020644cc(2) + 12;
            flag = 1;
        } else {
            out->byte = func_020644cc(2) + 14;
            flag = 1;
        }
    } else {
        if (((u8 *) &loc.c)[2] < 6) {
            out->byte = func_020644cc(3) + 16;
            flag = 1;
        } else if (func_02086108(func_0208602c(), 4) != 0) {
            out->byte = func_020644cc(3) + 22;
            flag = 1;
        } else {
            out->byte = 0x13;
            flag = 1;
        }
    }

    if (flag != 0) {
        return;
    }
    if (func_02099fe8() == -1) {
        return;
    }
    if (func_020644cc(2) != 0) {
        return;
    }
    out->byte = func_020644cc(3) + 25;
}
