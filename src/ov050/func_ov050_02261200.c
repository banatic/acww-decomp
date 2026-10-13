/* func_ov050_02261200 @ 0x02261200, 0xf4 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261200 {
    char pad_00[0xb4];
    char *unk_B4;
    char pad_B8[0xc4 - 0xb8];
    int unk_C4;
    char pad_C8[0xd0 - 0xc8];
    int unk_D0;
} UnkStruct_02261200;

extern int func_02099fe8(void);
extern int func_0201b43c(char *a, int b);
extern void func_ov050_02260dd4(UnkStruct_02261200 *self);
extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern void func_ov004_0224730c(void);
extern void func_ov004_022472ec(void);
extern void func_02034b80(u16 *p, int a, int b, int c);
extern void func_02034b04(u16 *p, int a, int b, int c);

void func_ov050_02261200(UnkStruct_02261200 *self, int mode)
{
    u16 tmp;
    u16 *p;
    int r;
    unsigned int ok;
    unsigned int in1;

    if (mode == 0) {
        if (func_02099fe8() < 0) {
            self->unk_D0 = 0x20;
        } else if (func_0201b43c(self->unk_B4, self->unk_C4) == 0) {
            self->unk_D0 = 0x21;
        } else {
            self->unk_D0 = 0x22;
            func_ov050_02260dd4(self);
        }
    } else if (mode == 1) {
        p = (u16 *) (self->unk_B4 + 0x732);
        if (func_0204bcdc(p) != 0) {
            tmp = 0xfff1;
            r = func_0204bc64(p);
            ok = (r == func_0204bc64(&tmp)) ? 1 : 0;
        } else {
            ok = (*p == 0xfff1) ? 1 : 0;
        }
        if (ok == 0) {
            in1 = 0;
            if (*(u16 *) (self->unk_B4 + 0x732) >= 0x1100 && *(u16 *) (self->unk_B4 + 0x732) <= 0x1143) {
                in1 = 1;
            }
            if (in1 != 0) {
                func_ov004_0224730c();
                func_02034b80((u16 *) (self->unk_B4 + 0x732), 0, 1, 1);
            } else {
                func_ov004_022472ec();
                func_02034b04((u16 *) (self->unk_B4 + 0x732), 0, 1, 1);
            }
        }
    }
}
