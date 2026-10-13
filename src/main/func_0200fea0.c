/* func_0200fea0 @ 0x0200fea0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_0200fea0 UnkStruct_0200fea0;
struct UnkStruct_0200fea0 {
    u8 pad_00[0x80c];
    int unk_80C; // offset 0x80c
    u8 pad_810[0x4];
    int unk_814; // offset 0x814
};

extern int func_020436a8(int arg);
extern int func_0200ffec(UnkStruct_0200fea0 *self);
extern void func_020431b8(int arg);

int func_0200fea0(UnkStruct_0200fea0 *self)
{
    int ret = 0;

    self->unk_814 = 0;

    if (self->unk_80C != -1) {
        ret = func_020436a8(self->unk_80C);

        switch (ret) {
            case 1:
            case 2:
                self->unk_814 = func_0200ffec(self);
                func_020431b8(self->unk_80C);
                self->unk_80C = -1;
                break;
        }
    }

    return ret;
}
