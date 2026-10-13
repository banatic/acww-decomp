/* func_ov004_022116c4 @ 0x022116c4, 0x34 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ee08(void *self, void *p);
extern void func_ov004_022118bc(void *self, int a);

void func_ov004_022116c4(char *self)
{
    void *p = *(void **) (self + 0x12c);
    char *q;

    if (p != 0 && *(int *) ((char *) p + 4) == 0) {
        q = self;
        if (self != 0) {
            q = q + 0xec;
        }
        func_0203ee08(self, q);
        func_ov004_022118bc(self, 4);
    }
}
