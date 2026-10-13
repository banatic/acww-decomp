/* func_ov004_02216cd0 @ 0x02216cd0, 0x24 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov004_02217124(void *self, int k);

void func_ov004_02216cd0(void *self)
{
    void *p = *(void **) ((char *) self + 0x12c);
    if (p != 0 && *(void **) ((char *) p + 4) == 0) {
        func_ov004_02217124(self, 0xb);
    }
}
