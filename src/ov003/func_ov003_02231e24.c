/* func_ov003_02231e24 @ 0x02231e24, 0xfc bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern void func_ov003_02231818(void *self, short *p);
extern void func_ov003_022316e0(void *self, short *p);
extern void func_ov003_02231af0(void *self, short *p);
extern void func_ov003_02231c80(void *self, short *p);
extern void func_ov003_02231be4(void *self, short *p);
extern void func_ov003_02232f78(void *self, short *p);
extern void func_ov003_022319bc(void *self, short *p);
extern void func_ov003_02233178(void *self, short *p);
extern void func_ov003_0223189c(void *self, short *p);
extern int func_ov003_02232598(void *self, int a);
extern void func_ov003_02230f60(void *self);
extern void func_ov003_02231d1c(void *self, short *p);

void func_ov003_02231e24(char *self)
{
    short *p;
    u8 s;

    p = (short *) (self + 0x242);
    s = *(u8 *) (self + 0x251);
    if (s != 0xb && s != 9 && s != 7) {
        if (*(signed char *) (self + 0x24d) == 0x1f) {
            func_ov003_02231818(self, p);
        } else {
            func_ov003_022316e0(self, p);
            *(char *) (self + 0x24a) = 0;
        }
    }
    switch (s) {
        case 3:
            func_ov003_02231af0(self, p);
            break;
        case 2:
            func_ov003_02231c80(self, p);
            break;
        case 1:
            func_ov003_02231be4(self, p);
            break;
        case 9:
            func_ov003_02232f78(self, p);
            *p = *p + 1;
            break;
        case 0xb:
            if (*(signed char *) (self + 0x24d) != 0x1f) {
                func_ov003_022319bc(self, p);
            } else {
                func_ov003_02233178(self, p);
            }
            break;
        case 7:
            *(char *) (self + 0x24a) = 1;
            func_ov003_0223189c(self, p);
            break;
        case 8:
            if (func_ov003_02232598(self, 2) != 0) {
                func_ov003_02230f60(self);
            }
            break;
        case 0x13:
            func_ov003_02231d1c(self, p);
            break;
    }
}
