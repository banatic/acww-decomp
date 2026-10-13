/* func_ov046_022606e0 @ 0x022606e0, 0x14 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

void func_ov046_022606e0(void *r0, int r1)
{
    if (r1 == 0) {
        *(int *) ((char *) r0 + 0xdc) = 7;
    } else {
        *(int *) ((char *) r0 + 0xdc) = 0xc;
    }
}
