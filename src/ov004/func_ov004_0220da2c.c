/* func_ov004_0220da2c @ 0x0220da2c, 0xc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_0220da2c(void *self, int v, int i)
{
    *(int *) ((char *) self + ((i & 1) << 2) + 0x10) = v;
}
