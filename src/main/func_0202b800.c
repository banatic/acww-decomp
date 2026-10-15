/* func_0202b800 @ 0x0202b800, 0xdc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0202b800 {
    unsigned char pad_00[0x830];
    int unk_830;
} UnkStruct_0202b800;

typedef struct UnkStruct_0202b800_2 {
    unsigned char pad_00[0x100];
    UnkStruct_0202b800 *unk_100;
    char unk_104[0x1e];
    u8 unk_122;
    unsigned char pad_123[0x12c - 0x123];
    int unk_12C;
    unsigned char pad_130[0x19c - 0x130];
    u16 unk_19C;
} UnkStruct_0202b800_2;

typedef struct Global {
    int unk_00;
    u8 unk_04;
} Global;

extern Global data_020c8b38;

extern int func_020819f0(int);
extern int func_02081d20(int);
extern void func_02081a04(int);
extern int func_02099fe8(void);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_02003704(int);
extern int func_02003648(int);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);

int func_0202b800(UnkStruct_0202b800_2 *self)
{
    int status;
    unsigned int v;

    status = 0;
    if (self->unk_12C == 0) {
        goto out;
    }

    v = 0;
    if (func_020819f0(self->unk_12C) == 0) {
        if (func_02081d20(self->unk_12C) >= 0x50) {
            if (func_02099fe8() != -1) {
                func_02081a04(self->unk_12C);
                status = 1;
            } else {
                status = 2;
            }
        } else {
            status = 3;
        }
    }

    func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                  data_020c8b38.unk_00, data_020c8b38.unk_04, status, 0);

    if (func_02003704(func_0208150c(self->unk_100->unk_830)) != 0) {
        v = func_02003648(func_0208150c(self->unk_100->unk_830));
    }

    self->unk_19C = (u16) (v < 0x9c ? 0x47d8 + v * 4 : 0x47d8);
    return 1;
out:
    return status;
}
