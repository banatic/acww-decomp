/* func_ov004_02230e94 @ 0x02230e94, 0x2c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020682e0(int k);
extern void func_02068320(void *p);
extern void func_ov004_0223121c(void *self, int k);

void func_ov004_02230e94(void *self)
{
    void *p = func_020682e0(0);
    if (*(void **) ((char *) p + 4) == 0) {
        func_02068320(p);
        *((char *) self + 0x63c) = 0;
        func_ov004_0223121c(self, 7);
    }
}
