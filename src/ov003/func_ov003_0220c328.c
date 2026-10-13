/* func_ov003_0220c328 @ 0x0220c328, 0xa8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov003_0220d1a8(void *self, void **out);
extern void func_0200fa1c(u32 *out, void *self, void *a, void *b, void *c);
extern int func_0201005c(void *self, u32 *buf, int len);
extern int func_0200ff28(void *self, u32 *buf, int flag, void *arg4);
extern int func_0200fd04(void *self, u32 *buf, int flag);
extern char data_ov003_02238130;

int func_ov003_0220c328(void *self, void *arg1, ...)
{
    u32 buf[3];

    if (func_ov003_0220d1a8(self, &arg1)) {
        return 1;
    }

    if (*(u32 *) ((char *) self + 0x170) == 1) {
        u32 tmp[3];
        func_0200fa1c(tmp, self, (char *) self + 0x5c, (char *) self + 0x8e, &data_ov003_02238130);
        buf[0] = tmp[0];
        buf[1] = tmp[1];
        buf[2] = tmp[2];
    } else {
        buf[0] = *(u32 *) ((char *) self + 0x158);
        buf[1] = *(u32 *) ((char *) self + 0x15c);
        buf[2] = *(u32 *) ((char *) self + 0x160);

        if (func_0201005c(self, buf, 0xc) == 0) {
            return 0;
        }
    }

    if (func_0200ff28(self, buf, 0, arg1) && func_0200fd04(self, buf, 0)) {
        return 1;
    }
    return 0;
}
