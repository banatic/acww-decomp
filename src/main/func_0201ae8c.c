/* func_0201ae8c @ 0x0201ae8c, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern volatile u8 data_020e54a8;
extern int func_02030890(void *self);
extern int func_ov004_0223c5a4(void *self);
extern void func_02034270(void *buf, void *self, int a, int b);
extern int func_020341c8(void *buf, int a);
extern int func_0203104c(void *self);
extern void func_0203423c(void *buf);

int func_0201ae8c(void *self)
{
    char buf[0x40];
    int result;
    int flag = (data_020e54a8 == 1) ? 1 : 0;

    if (flag != 0) {
        if (func_02030890(self) != -1) {
            return 1;
        }
        if (func_ov004_0223c5a4(self) != 0) {
            return 1;
        }
        return 0;
    }

    func_02034270(buf, self, 0, 0);
    if (*(int *) (buf + 0x30) != 0) {
        goto set1;
    }
    if (func_020341c8(buf, 1) > 0) {
        goto set1;
    }
    if (func_0203104c(self) == 0) {
        goto set0;
    }
set1:
    result = 1;
    goto tail;
set0:
    result = 0;
tail:
    func_0203423c(buf);
    return result;
}
