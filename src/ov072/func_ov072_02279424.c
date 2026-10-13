/* func_ov072_02279424 @ 0x02279424, 0xf4 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x564];
    char unk_564;
    char pad_565[0x718 - 0x565];
    u8 unk_718;
    char pad_719[3];
    int unk_71C;
    int unk_720;
} UnkStruct_02279424;

extern int func_ov072_02279618(UnkStruct_02279424 *self, void *p);
extern void func_02019c90(void *p, int a, int b, int c);
extern void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern int func_020644cc(int a);
extern unsigned short data_020c80f8;

int func_ov072_02279424(UnkStruct_02279424 *self)
{
    int r;

    if (self->unk_718 != 0) {
        if (func_ov072_02279618(self, &self->unk_720) == 2) {
            func_02019c90(&self->unk_564, 1, 0, data_020c80f8);
            return 1;
        }
        if (self->unk_720 == 1) {
            func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
            return 1;
        }
        if (func_ov072_02279618(self, &self->unk_71C) == 0) {
            r = func_020644cc(3);
            switch (r) {
                case 0:
                    func_02019c90(&self->unk_564, 1, 0xc, data_020c80f8);
                    break;
                case 1:
                    func_02019c90(&self->unk_564, 1, 0xd, data_020c80f8);
                    break;
                case 2:
                    func_02019c90(&self->unk_564, 1, 0xe, data_020c80f8);
                    break;
            }
            self->unk_71C = 0x190;
            self->unk_71C = self->unk_71C + func_020644cc(0x258);
            self->unk_720 = 0x7a;
        }
    }
    return 1;
}
