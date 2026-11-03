/* friend_roster_page: 3 functions, module ov119
 * mwccarm 1.2/base -O4,s
 * func_ov119_0229a49c @ 0x0229a49c, 0x48 bytes, Thumb
 * func_ov119_0229a46c @ 0x0229a46c, 0x30 bytes, Thumb
 * func_ov119_0229a434 @ 0x0229a434, 0x36 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_0229a434 {
    u8 pad_00[0xb3];
    u8 b3;
};

extern void func_0206fdd4(void *, int, int, int, int, int);
extern void func_ov119_0229a410(void *ptr, int a);

void func_ov119_0229a46c(void *param);

void func_ov119_0229a49c(void *self)
{
    int i;

    func_ov119_0229a46c(self);
    for (i = 0; i < 8; i++) {
        if (((unsigned char *) self)[0xb2] & (1 << i)) {
            int d = i * 2;
            func_0206fdd4((unsigned char *) self + 0xe0c, 3, d + 6, 4, d + 7, 5);
        }
    }
}

void func_ov119_0229a46c(void *param)
{
    func_0206fdd4((char *) param + 0x0e0c, 3, 6, 4, 0x15, 3);
    func_ov119_0229a410(param, 2);
}

void func_ov119_0229a434(struct UnkStruct_0229a434 *self)
{
    self->b3++;
    if (self->b3 == 10) {
        func_ov119_0229a49c((void *) self);
    } else if (self->b3 >= 25) {
        func_ov119_0229a46c((void *) self);
        self->b3 = 0;
    }
}
