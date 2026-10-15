/* func_02027804 @ 0x02027804, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u32 lo;
    u32 hi;
} U64;

extern "C" {
extern void func_0202da88(void *self, void *arg);
extern int func_020151c0(void *self);
extern void func_0202dbf0(void *self, U64 val);
extern u32 func_0209b4cc(u32 val, int mode);
extern u32 func_0208150c(u32 a);
extern void func_0207bae8(void *dst, u32 a, u32 b, int c);
extern void *func_02080ce4(u32 a);
extern int func_02068484(void *a, void *b, u32 c);
extern U64 data_020d94c8;
}

class Class {
  public:
    u8 pad_00[0x40];
    void *unk_40;
    u8 pad_44[0x6c];
    void (Class::*pmf)(void *ptr);
    u8 pad_B8[0x48];
    void *unk_100;
    u8 pad_104[0x20];
    u16 unk_124;
    u8 pad_126[0x3a];
    u32 unk_160;
};

extern unsigned char data_021c2bb4[];
extern unsigned char data_021e5a2c[];

extern "C" void func_02027804(Class *self)
{
    struct UnkStruct_02027804 {
        u8 type;
        u32 param;
        u8 other;
    } local;
    u32 r4 = *(u32 *) ((char *) self->unk_100 + 0x830);
    func_0202da88(self, (void *) data_021c2bb4);
    func_020151c0(self);
    func_0202dbf0(self, data_020d94c8);
    u32 r6 = func_0209b4cc(self->unk_160, 0);
    u32 r2 = func_0208150c(r4);
    func_0207bae8((void *) data_021e5a2c, r6, r2, 0x14);
    self->unk_124 = *(u16 *) func_02080ce4(r4);
    if (self->pmf) {
        (self->*self->pmf)(&local.param);
    }
    local.type = local.other;
    func_02068484(self->unk_40, &local, local.param);
}
