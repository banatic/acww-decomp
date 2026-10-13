/* func_ov004_0222f590 @ 0x0222f590, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ee08(void *self, void *a);
extern void func_ov004_0222f6e8(void *self, int k);
void func_ov004_0222f590(unsigned char *self)
{
    unsigned char *a, *p;
    p = *(unsigned char **) (self + 0x2d0);
    if (p != 0 && *(int *) (p + 4) == 0) {
        a = self;
        if (self != 0) {
            a = self + 0x290;
        }
        func_0203ee08(self, a);
        func_ov004_0222f6e8(self, 3);
    }
}
