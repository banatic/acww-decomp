/* func_ov045_02260848 @ 0x02260848, 0x110 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_020160b4(void);
extern int func_020ab504(void);
extern int func_0201b43c(void *a, int b);
extern int func_0202ea80(int a, int b);
extern void func_0206844c(void *a, void *b, void *c);
extern void *data_ov045_02261380;

struct UnkStruct_02260848 {
    char pad_00[0x1e];
    u8 unk_1E;
    char pad_1F[0x40 - 0x1f];
    void *unk_40;
    char pad_44[0xb4 - 0x44];
    void *unk_B4;
};

void func_ov045_02260848(struct UnkStruct_02260848 *self)
{
    int val;
    int r4;
    u8 c;

    func_020160b4();
    val = func_020ab504();
    r4 = 0xff;

    switch (self->unk_1E) {
        case 1:
        case 3:
        case 5:
            if (val == 0) {
                if (func_0201b43c(self->unk_B4, 100) == 0) {
                    r4 = 6;
                } else {
                    r4 = 7;
                }
            } else if (self->unk_1E == 5 && val == 1) {
                r4 = 0x14;
            }
            break;

        case 7:
        case 8:
            if (val == 0) {
                if (func_0202ea80(5, 0) != 0) {
                    r4 = 8;
                } else {
                    r4 = 0xd;
                    *(int *) ((char *) self->unk_B4 + 0x748) = 0;
                    func_0202ea80(5, 1);
                }
            } else if (val == 1) {
                if (func_0202ea80(4, 0) != 0) {
                    r4 = 8;
                } else {
                    r4 = 9;
                }
            }
            break;

        case 10:
            if (val == 0) {
                r4 = 0xc;
                *(int *) ((char *) self->unk_B4 + 0x748) = 1;
                func_0202ea80(4, 1);
            } else {
                r4 = 0xb;
            }
            break;

        case 20:
            if (val == 0) {
                if (func_0201b43c(self->unk_B4, 10000) == 0) {
                    r4 = 0x15;
                } else {
                    r4 = 0x17;
                }
            }
            break;
    }

    if (r4 != 0xff) {
        c = (u8) r4;
        func_0206844c(self->unk_40, &c, data_ov045_02261380);
    }
}
