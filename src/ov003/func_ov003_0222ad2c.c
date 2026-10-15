/* func_ov003_0222ad2c @ 0x0222ad2c, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_ov003_0222a784(void *self);
extern int func_ov003_0222a398(void *self);

void func_ov003_0222ad2c(void *self)
{
    if (*(u8 *) ((char *) self + 0x23c) == 1) {
        switch (*(u8 *) ((char *) self + 0x224)) {
            case 3:
            case 4:
            case 5:
                func_ov003_0222a784(self);
                break;
            case 6:
                break;
            default:
                if (func_ov003_0222a398(self) == 0) {
                    func_ov003_0222a784(self);
                }
                break;
        }
    }
}
