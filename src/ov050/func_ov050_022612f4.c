/* func_ov050_022612f4 @ 0x022612f4, 0x9c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0xb4];
    u8 *data;
} UnkStruct_022612f4;

extern int func_0204bcdc(const u16 *);
extern int func_0204bc64(const u16 *);
extern int func_02034aa8(int);
extern int func_02034a74(int);
extern int func_0203aeac(void);
extern void func_ov050_02261390(UnkStruct_022612f4 *, int);

void func_ov050_022612f4(UnkStruct_022612f4 *self, int arg1)
{
    u16 *p;
    int r;

    p = (u16 *) (self->data + 0x732);

    if (func_0204bcdc(p)) {
        u16 key = 0xfff1;
        if (func_0204bc64(p) == func_0204bc64(&key)) {
            r = 1;
        } else {
            r = 0;
        }
    } else {
        if (*p == 0xfff1) {
            r = 1;
        } else {
            r = 0;
        }
    }

    if (!r) {
        int inRange = 0;
        u16 v;

        v = *(u16 *) (self->data + 0x732);
        if (v >= 0x1100 && v <= 0x1143) {
            inRange = 1;
        }

        if (inRange) {
            func_02034aa8(1);
        } else {
            func_02034a74(1);
        }

        func_0203aeac();
    }

    func_ov050_02261390(self, arg1);
}
