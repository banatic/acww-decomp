/* func_ov068_02272db4 @ 0x02272db4, 0x14 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov068_02272db4(void *self);

int func_ov068_02272db4(void *self)
{
    if (*(int *) ((char *) self + 0x2b4) != 0) {
        return 1;
    }
    return 0;
}
