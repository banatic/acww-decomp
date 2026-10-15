/* func_02027914 @ 0x02027914, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02027914 {
    int unk_00;
    u8 unk_04;
    u8 pad[3];
};
struct UnkStruct_02027914_2 {
    u8 unk_00;
    u8 pad[3];
};
struct UnkStruct_02027914_3 {
    u16 unk_00;
};

struct UnkStruct_02027914_4;
typedef void (UnkStruct_02027914_4::*PMF)(UnkStruct_02027914 *);

struct UnkStruct_02027914_4 {
    u8 pad_00[0x40];
    int unk_40;
    u8 pad_44[0x6c];
    PMF cb;
    u8 pad_B8[0x48];
    u8 *unk_100;
    u8 pad_104[0x20];
    UnkStruct_02027914_3 unk_124;
    u8 pad_126[0x3a];
    void *unk_160;
};

extern u8 data_021c2b24;
extern u8 data_021c2b3c;
extern u8 data_021c2b54;

extern "C" {
extern u8 *func_020808b0(void *);
extern int func_0204c228(UnkStruct_02027914_3 *);
extern void func_0209b40c(void *, int);
extern void func_0202da88(UnkStruct_02027914_4 *, void *);
extern int func_02068484(int, UnkStruct_02027914_2 *, int);

void func_02027914(UnkStruct_02027914_4 *o)
{
    int mode;
    unsigned int ok;
    int id;
    u8 *tbl;
    UnkStruct_02027914_2 x;
    UnkStruct_02027914 y;

    mode = 1;
    tbl = func_020808b0(*(void **) (o->unk_100 + 0x830));
    ok = 0;
    if (o->unk_124.unk_00 >= 0x11a8 && o->unk_124.unk_00 <= 0x12a7) {
        ok = 1;
    }
    if (ok != 0) {
        id = func_0204c228(&o->unk_124);
        if (id == tbl[0]) {
            mode = 0;
        } else if (id == tbl[1]) {
            mode = 2;
        }
    }
    func_0209b40c(o->unk_160, mode);
    switch (mode) {
        case 0:
            func_0202da88(o, &data_021c2b24);
            break;
        case 2:
            func_0202da88(o, &data_021c2b3c);
            break;
        default:
            func_0202da88(o, &data_021c2b54);
            break;
    }
    if (o->cb != 0) {
        (o->*(o->cb))(&y);
    }
    x.unk_00 = y.unk_04;
    func_02068484(o->unk_40, &x, y.unk_00);
}
}
