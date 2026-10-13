/* func_ov002_02209464 @ 0x02209464, 0x50 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02209464 {
    u8 pad_00[8];
    int unk_08;
    int unk_0C;
    u8 pad_10[0xa];
    u8 unk_1A;
};

extern void func_ov002_022083b8(char *p, int a, int b, int c);
extern int func_ov002_02208780(char *p);
extern void func_0208f210(char *p, int a, int b);
extern void func_0208aa60(char *p, int a, int b);

void func_ov002_02209464(struct UnkStruct_02209464 *self)
{
    int w;

    func_ov002_022083b8((char *) self + 0x3b0, self->unk_1A, -self->unk_08, -self->unk_0C);
    w = func_ov002_02208780((char *) self + 0x3b0);
    func_0208f210((char *) self + 0x26c, 0, w);
    func_0208aa60((char *) self + 0x2e4, 0, -(w >> 2));
}
