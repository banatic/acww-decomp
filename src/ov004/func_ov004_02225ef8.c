/* func_ov004_02225ef8 @ 0x02225ef8, 0x78 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov004_0223cb10(void);
extern void *func_ov004_0223cadc(void *a, int b);
extern int *func_ov004_0223cb24(void *h);
extern int func_ov004_0223cb18(void *h);
extern int func_ov004_0222a494(void *self, int a, int b, int c, int d, int e);
extern int func_0200fbe0(void *self);
extern int func_02010004(void *self, int a);

int func_ov004_02225ef8(char *self)
{
    volatile int v[3];
    void *h;
    int *p;

    if (*(unsigned char *) (self + 0x141) != 0) {
        h = func_ov004_0223cadc(func_ov004_0223cb10(), 0);
        if (h == 0) {
            return 0;
        }
        p = func_ov004_0223cb24(h);
        v[0] = p[0];
        v[1] = p[1];
        v[2] = p[2];
        return func_ov004_0222a494(self, v[0], v[2], func_ov004_0223cb18(h), 5, -1);
    }
    if (*(unsigned char *) (self + 0x148) != 0) {
        return func_02010004(self, func_0200fbe0(self));
    }
    return 0;
}
