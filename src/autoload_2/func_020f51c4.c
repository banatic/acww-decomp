/* func_020f51c4 @ 0x020f51c4, 0xdc bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct UnkStruct_020f51c4 {
    char pad_00[0x3a];
    u16 unk_3A;
} UnkStruct_020f51c4;

typedef struct UnkStruct_020f51c4_2 {
    char pad_00[8];
    UnkStruct_020f51c4 *unk_08;
    char pad_0C[0x18 - 0xc];
    u16 unk_18;
} UnkStruct_020f51c4_2;

extern void func_020eed18(void *p, int k);
extern void func_020eedb8(u16 m, int k, void *p);
extern void func_020f50e4(UnkStruct_020f51c4_2 *s);

void func_020f51c4(UnkStruct_020f51c4_2 *s)
{
    unsigned int ok;
    int a;
    int b;
    UnkStruct_020f51c4 *p;

    p = s->unk_08;
    a = 0;
    ok = (p != 0);
    if (ok) {
        if (p->unk_3A != s->unk_18 % 1000) {
            b = 1;
            a = b;
        } else {
            b = 0;
            a = b;
        }
    } else {
        b = 1;
    }
    if (a) {
        func_020eed18(&s->unk_08, 5);
    }
    if (b) {
        func_020eedb8((u16) (s->unk_18 % 1000), 1, &s->unk_08);
    }
    func_020f50e4(s);
}
