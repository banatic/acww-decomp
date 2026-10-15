/* func_ov004_02235eac @ 0x02235eac, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_02239bb4(void *p, int a, int b);

void func_ov004_02235eac(void *self)
{
    int *p;

    p = (int *) ((char *) self + 0x20c);
    *p = *(int *) ((char *) self + 0x210) - *(int *) ((char *) self + 0x218) * *(int *) ((char *) self + 0x158);
    func_ov004_02239bb4((char *) self + 0x1a8, *p, *(short *) ((char *) self + 0x1c0));
    if (*(int *) ((char *) self + 0x20c) <= 0xf6) {
        *(int *) ((char *) self + 0x20c) = 0xf6;
        *(int *) ((char *) self + 0x158) = 3;
        *((char *) self + 0x1ee) = 2;
    }
}
