/* func_ov004_0220d9f8 @ 0x0220d9f8, 0xc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

int func_ov004_0220d9f8(void *self, int i)
{
    return *(int *) ((char *) self + ((i & 1) << 2) + 0x8);
}
