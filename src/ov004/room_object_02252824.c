/* room_object_02252824: 3 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02214598 @ 0x02214598, 0x78 bytes, Thumb
 * func_ov004_02214568 @ 0x02214568, 0x30 bytes, Thumb
 * func_ov004_022144e0 @ 0x022144e0, 0x88 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_02214598 {
    char pad_00[4];
    u16 unk_04;
};

extern void func_ov004_0220d280(void *p, int a, int b);
extern void *func_ov004_0220e220(void *p);
extern void *func_ov004_0220d9f8(void *p, int a);
extern int func_02055e00(void *p);
extern void func_02056440(void *p, int a, void *b, int c, int d, int e);
extern int func_0205265c(unsigned int argument0, int argument1, int argument2, int argument3);
extern int func_ov004_0220d2a8(char *argument0);
extern int func_ov004_022107d4(char *argument0);
extern int func_ov004_0221081c(char *argument0);
extern int func_ov004_0220e4b0(void *p);
extern int func_ov004_02210744(void *self);

int func_ov004_02214598(char *self)
{
    struct UnkStruct_02214598 *p;

    func_ov004_0220d280(self + 0x740, 1, 0);
    if (func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), 0) != 0) {
        p = (struct UnkStruct_02214598 *) func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), 0);
        func_02056440(self + 0x7c4, func_02055e00(self + 0x538), p, 1, 0x1000, (u16) (p->unk_04 - 1));
    }
    return 1;
}

int func_ov004_02214568(char *self)
{
    // DECLS
    int v3;
    // ENDDECLS
    func_ov004_0221081c(self);
    func_ov004_022107d4(self);
    v3 = func_ov004_0220d2a8(self + 0x740);
    if (v3 != 0x0) {
        return func_0205265c((unsigned int) (self), (int) (0x3), (int) (0xff), (int) (0x1));
    }
    return v3;
}

int func_ov004_022144e0(char *self)
{
    struct UnkStruct_022144e0 {
        char pad[4];
        unsigned short f4;
    } *p;

    func_ov004_0220d280(self + 0x740, 0, 0);
    if (func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), 0) != 0) {
        p = (struct UnkStruct_022144e0 *) func_ov004_0220d9f8(func_ov004_0220e220(self + 0x6cc), 0);
        if (func_ov004_0220e4b0(self + 0x7c4) != 0) {
            func_02056440(self + 0x7c4, func_02055e00(self + 0x538), p, 3, 0x1000, (unsigned short) (p->f4 - 1));
        }
    }
    func_ov004_02210744(self);
    return 1;
}
