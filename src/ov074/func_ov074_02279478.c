/* func_ov074_02279478 @ 0x02279478, 0x22 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov074_0227949c(void *);

int func_ov074_02279478(void *self)
{
    if (*(int *) ((char *) self + 0x98) != 0) {
        if (func_ov074_0227949c(self)) {
            return 1;
        }
    }
    return 0;
}
