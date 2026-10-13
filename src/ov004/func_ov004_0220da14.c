/* func_ov004_0220da14 @ 0x0220da14, 0xc bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

void func_ov004_0220da14(void *self, int v, int i)
{
    *(int *) ((char *) self + ((i & 1) << 2) + 0x20) = v;
}
