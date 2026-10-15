/* func_ov004_02217c70 @ 0x02217c70, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203ee08(void *self, void *p);
extern int func_0203e020(void *self);
extern int func_020b5e10(void);
extern int func_020b6434(int a, int b, int c, int d);
extern void func_020a1948(void);

void func_ov004_02217c70(char *self)
{
    void *p = *(void **) (self + 0x12c);
    char *q;

    if (p != 0 && *(int *) ((char *) p + 4) == 0) {
        q = self;
        if (self != 0) {
            q = q + 0xec;
        }
        func_0203ee08(self, q);
        func_0203e020(self);
        func_020b6434(func_020b5e10(), 0x2e, 2, 0);
        func_020a1948();
    }
}
