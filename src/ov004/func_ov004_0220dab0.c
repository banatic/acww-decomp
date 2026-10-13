/* func_ov004_0220dab0 @ 0x0220dab0, 0xc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

int func_ov004_0220dab0(void *self, int i)
{
    return *(int *) ((char *) self + ((i & 3) << 2) + 0x4);
}
