/* func_0206108c @ 0x0206108c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct OSOwnerInfo {
    u8 language;
    u8 favoriteColor;
    u8 birthday[2];
    u16 nickName[10];
    u16 nickNameLength;
    u16 comment[26];
    u16 commentLength;
} OSOwnerInfo;

typedef struct Flags {
    u32 f0 : 3;
    u32 f1 : 3;
    u32 f2 : 4;
    u32 f3 : 4;
    u32 f4 : 4;
    u32 f5 : 14;
} Flags;

typedef struct Parent {
    u8 pad_00[0x1594];
    u8 unk_1594[9];
    u8 pad_159D[3];
    Flags flags; // offset 0x15a0
} Parent;

extern void func_0206126c(void *p, int idx);
extern void func_02060974(u8 *p);
extern void OS_GetOwnerInfo(OSOwnerInfo *info);

void func_0206108c(Parent *self)
{
    int i;
    u8 *p;
    OSOwnerInfo info;

    p = (u8 *) self;
    for (i = 0; i < 5; i++) {
        func_0206126c(p, i);
        p += 0x450;
    }
    self->flags.f0 = 0;
    func_02060974((u8 *) self + 0x1594);
    OS_GetOwnerInfo(&info);
    self->flags.f3 = info.favoriteColor;
    self->flags.f2 = self->flags.f3;
    self->flags.f4 = 0;
}
