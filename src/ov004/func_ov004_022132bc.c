/* func_ov004_022132bc @ 0x022132bc, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02004044(void *dst, int *v);

int func_ov004_022132bc(char *self)
{
    int t[3];

    t[0] = *(int *) (self + 0x7b8);
    t[1] = *(int *) (self + 0x7bc);
    t[2] = *(int *) (self + 0x7c0);
    func_02004044(self + 0x844, t);
    return 1;
}
