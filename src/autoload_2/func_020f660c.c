/* func_020f660c @ 0x020f660c, 0xe4 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x14];
    u8 unk_14[0x14];
    u8 unk_28[0x11];
    u8 unk_39;
    u8 unk_3A;
    u8 unk_3B;
    u8 unk_3C;
} UnkStruct_020f660c;

extern int func_020f5e50(void *, int);
extern int func_020f5e24(int);
extern int func_020f5c64(void *, int);
extern void func_020f6580(UnkStruct_020f660c *, int);
extern int func_020f6564(UnkStruct_020f660c *, int);
extern int func_020f7054(void *, u16, void *);

void func_020f660c(UnkStruct_020f660c *self, void *p, unsigned int idx)
{
    int c1, c2;

    if ((u8) (self->unk_3C + 0xff) <= 1) {
        return;
    }

    self->unk_39 = (u8) func_020f5e24(func_020f5e50(p, 0));
    self->unk_3A = (u8) func_020f5c64(p, 0);
    self->unk_3C = 4;

    switch (idx) {
        case 0:
            c1 = 0x25f;
            c2 = 0xd4;
            break;
        case 1:
            c1 = 0x262;
            c2 = 0xd7;
            break;
        case 2:
            c1 = 0x260;
            c2 = 0xd5;
            break;
        case 3:
            c1 = 0x261;
            c2 = 0xd6;
            break;
        default:
            return;
    }

    func_020f6580(self, c1);
    func_020f6564(self, c2);
    func_020f7054(&self->unk_14, (u16) c2, &self->unk_28);
    return;
}
