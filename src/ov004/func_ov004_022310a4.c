/* func_ov004_022310a4 @ 0x022310a4, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_0223121c(void *self, int k);

void func_ov004_022310a4(void *self)
{
    void *p = *(void **) ((char *) self + 0x2d0);
    if (p != 0 && *(void **) ((char *) p + 4) == 0) {
        func_ov004_0223121c(self, 0x5);
    }
}
