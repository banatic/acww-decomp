/* func_0201ec58 @ 0x0201ec58, 0x110 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0201ec58;
typedef void (UnkStruct_0201ec58::*PMF)(int);

struct UnkStruct_0201ec58_2 {
    u8 pad_00[0x830];
    int v;
};

struct UnkStruct_0201ec58 {
    u8 pad_00[0xb0];
    PMF cb;
    u8 pad_B8[0x100 - 0xb8];
    UnkStruct_0201ec58_2 *q;
    u8 pad_104[0x128 - 0x104];
    int unk_128;
    int unk_12C;
};

extern "C" int func_0208675c(void *s);
extern "C" int func_02020a5c(UnkStruct_0201ec58 *p, int a2);
extern "C" void func_0202d8f8(UnkStruct_0201ec58 *p, int *a, int *b, int n, int z);
extern "C" int func_0203fdc4(int k);
extern "C" int func_020819bc(int x);
extern "C" int func_020644cc(int k);
extern "C" int func_02003704(int x);
extern "C" void func_0202da88(UnkStruct_0201ec58 *p, void *s);
extern "C" void func_020819e0(int x);
extern u8 data_021f3aa4[];
extern u8 data_021c2044[];
extern u8 data_021c205c[];
extern u8 data_021c2074[];

extern "C" void func_0201ec58(UnkStruct_0201ec58 *p, int a2)
{
    int n;
    int v;
    int m;

    n = p->q->v;
    v = func_0208675c(data_021f3aa4);
    m = 2;
    if (func_02020a5c(p, a2)) {
        func_0202d8f8(p, &p->unk_12C, &p->unk_128, n, 0);
        return;
    }
    if (func_0203fdc4(0x11) == 6 && p->unk_12C != 0 && func_020819bc(p->unk_12C) != 0) {
        m = 3;
    }
    m = func_020644cc(m);
    if (p->unk_12C == 0 || func_020819bc(p->unk_12C) == 0 || m == 2) {
        func_0202da88(p, data_021c2044);
    } else if (m == 0 && func_02003704(v)) {
        func_0202da88(p, data_021c205c);
    } else {
        func_0202da88(p, data_021c2074);
    }
    if (p->cb) {
        (p->*(p->cb))(a2);
    }
    func_0202d8f8(p, &p->unk_12C, &p->unk_128, n, 0);
    if (p->unk_12C != 0) {
        func_020819e0(p->unk_12C);
    }
}
