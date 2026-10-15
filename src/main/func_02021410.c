/* func_02021410 @ 0x02021410, 0xd0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 a : 2;
    u8 b : 3;
    u8 c : 3;
} Flags;

typedef struct UnkStruct_02021410 {
    char pad[0x830];
    int unk_830;
} UnkStruct_02021410;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Cfg;

typedef struct UnkStruct_02021410_2 {
    char pad_00[0x100];
    UnkStruct_02021410 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
} UnkStruct_02021410_2;

typedef struct {
    Flags unk_00;
    u8 pad[3];
    int b0;
    int b1;
} Agg;

extern Cfg data_020c8bb8;
extern u8 data_020c8934[];

extern void func_0209e474(void *p);
extern int func_02088470(int a, int b, int c, Flags *d);
extern int func_0208150c(int x);
extern int func_020036e8(int x);
extern int func_0202da38(UnkStruct_02021410_2 *self, char *a, unsigned char *b, int n, int e, int f, int g, int h, int i);

int func_02021410(UnkStruct_02021410_2 *self)
{
    // DECLS
    int ret;
    int mode;
    int sel;
    int idx;
    Agg agg;
    unsigned int k;
    // ENDDECLS

    mode = data_020c8bb8.unk_04;
    idx = 0;
    agg.b0 = 0;
    agg.b1 = 0;
    sel = -1;
    ret = 0;
    func_0209e474(&agg.b0);
    if (func_02088470(((u8 *) &agg)[9], ((u8 *) &agg)[8], ((u8 *) &agg)[7], &agg.unk_00) != 0) {
        if (agg.unk_00.a == 2 && agg.unk_00.b == 3) {
            sel = 1;
        } else {
            sel = 0;
        }
    }
    switch (sel) {
        case 0:
            k = agg.unk_00.a;
            if (k >= 4) {
                k = 0;
            }
            idx = data_020c8934[k];
            ret = 1;
            break;
        case 1:
            mode = 1;
            idx = agg.unk_00.c + 0xc;
            ret = mode;
            break;
    }
    if (ret == 1) {
        func_0202da38(self, self->unk_104, &self->unk_122, 0x1e, func_020036e8(func_0208150c(self->unk_100->unk_830)),
                      data_020c8bb8.unk_00, mode, idx, 0);
    }
    return ret;
}
