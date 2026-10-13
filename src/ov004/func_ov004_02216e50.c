/* func_ov004_02216e50 @ 0x02216e50, 0x56 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223cb10(void);
extern void *func_ov004_0223ca9c(int x, void *self);
extern int func_ov004_02217230(void *self);
extern int func_ov004_0223cb18(void *h);
extern char *func_ov004_0223cb24(void *h);
extern void func_ov004_0222c030(int *t, char *p, char *q, short *a);

int func_ov004_02216e50(void *self)
{
    short a;
    int t;
    void *h;
    char *p;

    h = func_ov004_0223ca9c(func_ov004_0223cb10(), self);
    t = func_ov004_02217230(self);
    if (t != -1) {
        a = (short) func_ov004_0223cb18(h);
        p = func_ov004_0223cb24(h);
        func_ov004_0222c030(&t, p, func_ov004_0223cb24(h) + 8, &a);
        return 1;
    }
    return 1;
}
