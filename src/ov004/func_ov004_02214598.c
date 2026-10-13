/* func_ov004_02214598 @ 0x02214598, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov004_0220d280(void *p, int a, int b);
extern void *func_ov004_0220e220(void *p);
extern void *func_ov004_0220d9f8(void *p, int a);
extern int func_02055e00(void *p);
extern void func_02056440(void *p, int a, void *b, int c, int d, int e);

struct UnkStruct_02214598 {
    char pad_00[4];
    u16 unk_04;
};

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
