/* func_02020268 @ 0x02020268, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct Global {
    int unk_00;
    u8 unk_04;
} Global;
typedef struct UnkStruct_02020268_2 {
    char pad_00[0x830];
    unsigned char *unk_830;
} UnkStruct_02020268_2;
typedef struct Pair {
    int a, b;
} Pair;

typedef struct UnkStruct_02020268_3 {
    char pad_00[0xc8];
    Pair pairC8;
    char pad_D0[0x100 - 0xd0];
    UnkStruct_02020268_2 *unk_100;
    char unk_104[0x1e];
    u8 unk_122;
} UnkStruct_02020268_3;

typedef struct UnkStruct_02020268_4 {
    char *unk_00;
    u8 unk_04;
} UnkStruct_02020268_4;

typedef union UnkStruct_02020268 {
    int w[2];
    u8 b[8];
} UnkStruct_02020268;

extern int func_02020a5c(void *self, void *out);
extern u32 func_020644cc(int n);
extern void func_0209e474(void *p);
extern int func_0209de44(int a, int b, int c, int d);
extern unsigned char *func_0208150c(unsigned char *a);
extern int func_020036e8(unsigned char *a);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern Global data_020c8c68;
extern Pair data_020d8e88;

void func_02020268(UnkStruct_02020268_3 *self, UnkStruct_02020268_4 *out)
{
    UnkStruct_02020268 loc;
    unsigned char *t;
    u32 sel;

    t = self->unk_100->unk_830;
    if (func_02020a5c(self, out) == 0) {
        loc.w[0] = 0;
        loc.w[1] = 0;
        sel = func_020644cc(10) & 1;
        func_0209e474(&loc);
        if (sel == 0) {
            u32 v = loc.b[2];
            if (v < 0x13) {
                sel = 2;
            } else if (v < 0x14) {
                sel = 0;
            } else if (v < 0x16) {
                sel = 1;
            } else {
                sel = 2;
            }
        } else {
            int c = loc.b[3];
            if (c != 0) {
                sel = (c - 1) / 7;
            } else {
                sel = 0;
            }
            if (func_0209de44(loc.b[5], loc.b[4], 6, 5) != -1 && sel >= 2) {
                sel--;
            }
            if (sel >= 5) {
                sel = 0;
            }
            sel = (u32) sel + 3;
        }
        func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(t)), data_020c8c68.unk_00,
                      data_020c8c68.unk_04, sel, 0);
        out->unk_00 = self->unk_104;
        out->unk_04 = self->unk_122;
    }
    self->pairC8 = data_020d8e88;
}
