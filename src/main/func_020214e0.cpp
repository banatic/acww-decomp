/* func_020214e0 @ 0x020214e0, 0x114 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020214e0 {
    int a;
    int b;
};
struct UnkStruct_020214e0_2 {
    int unk_00;
    int unk_04;
    u8 unk_08;
    u8 unk_09;
    u8 pad[2];
};

struct UnkStruct_020214e0_4 {
    u8 pad[0x830];
    int unk_830;
};
struct UnkStruct_020214e0_3 {
    u8 pad_00[0x100];
    UnkStruct_020214e0_4 *unk_100;
    u8 unk_104[0x122 - 0x104];
    u8 unk_122[2];
};

typedef int (UnkStruct_020214e0_3::*PMF)(u8 *, int *, u8 *, UnkStruct_020214e0 *);

extern PMF data_020d90c0;
extern PMF data_020d90a8;

extern "C" {
extern char *func_02137550(void *, unsigned int);
extern void func_0209e474(UnkStruct_020214e0 *);
extern int func_020644cc(int);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(UnkStruct_020214e0_3 *, u8 *, u8 *, int, int, int, int, int, int);

int func_020214e0(UnkStruct_020214e0_3 *obj)
{
    static PMF tbl[2] = {data_020d90c0, data_020d90a8};
    UnkStruct_020214e0 s;
    UnkStruct_020214e0_2 buf[2];
    UnkStruct_020214e0_2 *p;
    int i;

    func_02137550(buf, 0x18);
    p = 0;
    s.a = 0;
    s.b = 0;
    func_0209e474(&s);
    for (i = 0; i < 2; i++) {
        buf[i].unk_00 = (obj->*tbl[i])(&buf[i].unk_08, &buf[i].unk_04, &buf[i].unk_09, &s);
    }
    if (buf[0].unk_00) {
        if (buf[1].unk_00 && func_020644cc(2) == 0) {
            p = &buf[1];
        } else {
            p = &buf[0];
        }
    } else if (buf[1].unk_00) {
        p = &buf[1];
    }
    if (p) {
        func_0202da38(obj, obj->unk_104, obj->unk_122, 0x1e, func_020036e8(func_0208150c(obj->unk_100->unk_830)), p->unk_00,
                      p->unk_08, p->unk_04, p->unk_09);
        return 1;
    }
    return 0;
}
}
