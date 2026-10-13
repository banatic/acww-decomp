/* func_0201cbec @ 0x0201cbec, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0201cbec {
    u8 pad_00[0x8e];
    s16 unk_8E;
    u8 pad_90[0x478 - 0x90];
    u32 unk_478;
    u32 unk_47C;
    u32 unk_480;
};

extern int func_0201cbac(void *p1, struct UnkStruct_0201cbec *p2, void *p3, void *p4);
extern void func_020044c0(void *p1, void *p4, int c, int d);
extern void func_020912d4(void *p3, u32 *arr, short *s, int d);

void func_0201cbec(void *p1, struct UnkStruct_0201cbec *p2, void *p3, void *p4)
{
    u32 local[3];
    short s;

    if (func_0201cbac(p1, p2, p3, p4) == 0) {
        return;
    }

    local[0] = p2->unk_478;
    local[1] = p2->unk_47C;
    local[2] = p2->unk_480;
    s = p2->unk_8E;

    func_020044c0(p1, p4, 0x7f, 0);
    func_020912d4(p3, local, &s, 0);
}
