/* func_ov050_02261bb8 @ 0x02261bb8, 0xc4 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261bb8 {
    char pad_00[0xb4];
    char *unk_B4;
    char pad_B8[0xd0 - 0xb8];
    int unk_D0;
} UnkStruct_02261bb8;

extern int func_0204bcdc(u16 *p);
extern int func_0204bc64(u16 *p);
extern int func_02060de4(void *tbl, u8 idx);
extern int data_021ebcd4;

void func_ov050_02261bb8(UnkStruct_02261bb8 *self)
{
    u16 tmp;
    u16 *p;
    int r;
    unsigned int ok;
    unsigned int in1;
    unsigned int in2;
    u16 v;

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
        if (*(u16 *) (self->unk_B4 + 0x732) >= 0x1521 && *(u16 *) (self->unk_B4 + 0x732) <= 0x1530) {
            in1 = 1;
        }
        if (in1 != 0) {
            self->unk_D0 = 0x2f;
            in2 = 0;
            v = *(u16 *) (self->unk_B4 + 0x732);
            if (v >= 0x1521 && v <= 0x1530) {
                in2 = 1;
            }
            func_02060de4(&data_021ebcd4, (u8) (in2 != 0 ? v - 0x1521 : -1));
        } else {
            self->unk_D0 = 0x23;
        }
    }
}
