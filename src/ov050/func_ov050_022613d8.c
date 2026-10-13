/* func_ov050_022613d8 @ 0x022613d8, 0xa8 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_022613d8 {
    char pad_00[0xb4];
    char *unk_B4;
    char pad_B8[0xc4 - 0xb8];
    int unk_C4;
    char pad_C8[0xd0 - 0xc8];
    int unk_D0;
} UnkStruct_022613d8;

extern int func_0201b43c(char *a, int b);
extern void func_0201b420(char *a, int b);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern void func_020ad944(u16 *p);

void func_ov050_022613d8(UnkStruct_022613d8 *self, int mode)
{
    u16 tmp;
    u16 *p;
    int r;
    unsigned int ok;

    if (mode == 0) {
        if (func_0201b43c(self->unk_B4, self->unk_C4) != 0) {
            func_0201b420(self->unk_B4, self->unk_C4);
            self->unk_D0 = 0x1c;
            p = (u16 *) (self->unk_B4 + 0x732);
            if (func_0204bcdc(p) != 0) {
                tmp = 0xfff1;
                r = func_0204bc64(p);
                ok = (r == func_0204bc64(&tmp)) ? 1 : 0;
            } else {
                ok = (*p == 0xfff1) ? 1 : 0;
            }
            if (ok == 0) {
                func_020ad944((u16 *) (self->unk_B4 + 0x732));
            }
        } else {
            self->unk_D0 = 0x1d;
        }
    } else {
        self->unk_D0 = 0x1b;
    }
}
