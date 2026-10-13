/* func_0202a1cc @ 0x0202a1cc, 0x120 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0202a1cc {
    u8 pad_00[0x20];
    u8 a;
    u8 b;
    u8 pad_22[6];
} UnkStruct_0202a1cc;

typedef struct UnkStruct_0202a1cc_2 {
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad_44[0x160 - 0x44];
    void *unk_160;
} UnkStruct_0202a1cc_2;

extern void *func_0209bbf8(int a);
extern void *func_0209ad9c(int a, void *b);
extern void func_0201cfb4(UnkStruct_0202a1cc_2 *p, UnkStruct_0202a1cc *loc);
extern void *func_0209b4d4(void *h);
extern void func_0202d9d0(UnkStruct_0202a1cc_2 *p, void *x);
extern void *func_0209b4cc(void *h, int i);
extern void func_02015e10(UnkStruct_0202a1cc_2 *p, void *x, int i);
extern void func_0202d9c4(UnkStruct_0202a1cc_2 *p);
extern void *func_0209bb70(void);
extern void func_02015de4(UnkStruct_0202a1cc_2 *p, void *x, int a, int b);
extern int func_0209b414(void *h);
extern void func_0201cf90(UnkStruct_0202a1cc_2 *p, UnkStruct_0202a1cc *loc, int a, int b, int c, void *s);
extern void func_0201cf74(UnkStruct_0202a1cc_2 *p, UnkStruct_0202a1cc *loc, int i, void *d, void *s);
extern void func_0201cec8(UnkStruct_0202a1cc_2 *p, UnkStruct_0202a1cc *loc);
typedef struct UnkStruct_0202a1cc_3 {
    int a;
    int b;
} UnkStruct_0202a1cc_3;
extern void func_0202da74(UnkStruct_0202a1cc_2 *p, UnkStruct_0202a1cc_3 s);
extern void func_02068388(void *x, int i);
extern u8 data_021c2be4[];
extern u8 data_021c2bcc[];
extern u8 data_021c1e14[];
extern u8 data_021c1d6c[];
extern u8 data_020c8928[];
extern u8 data_020c8924[];
extern UnkStruct_0202a1cc_3 data_020d9490;

int func_0202a1cc(UnkStruct_0202a1cc_2 *p, int a2, int a3, int a4)
{
    int ok;
    UnkStruct_0202a1cc loc;

    ok = 0;
    p->unk_160 = func_0209ad9c(a3, func_0209bbf8(a4));
    if (p->unk_160 != 0) {
        func_0201cfb4(p, &loc);
        func_0202d9d0(p, func_0209b4d4(p->unk_160));
        func_02015e10(p, func_0209b4cc(p->unk_160, 0), 0);
        func_02015e10(p, func_0209b4cc(p->unk_160, 1), 1);
        func_0202d9c4(p);
        func_02015de4(p, func_0209bb70(), 0, 7);
        if (func_0209b414(p->unk_160)) {
            func_0201cf90(p, &loc, 0, 0x23, 0x23, data_021c2be4);
        } else {
            func_0201cf90(p, &loc, 0, 0x1e, 0x1e, data_021c2bcc);
        }
        func_0201cf74(p, &loc, 1, data_020c8928, data_021c1e14);
        func_0201cf74(p, &loc, 2, data_020c8924, data_021c1d6c);
        loc.a = 3;
        loc.b = (u8) (loc.a - 1);
        func_0201cec8(p, &loc);
        func_0202da74(p, data_020d9490);
        func_02068388(p->unk_40, 1);
        ok = 1;
    }
    return ok;
}
