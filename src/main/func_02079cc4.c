/* func_02079cc4 @ 0x02079cc4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
} Pair;

extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);
extern char *func_02079350(void);
extern void func_020794d4(char *e, int k);
extern void func_0209e474(Pair *pr);
extern int func_0207a118(void *p0, Pair *pr);
extern void func_02079db8(void *p0, void *p1);
extern void func_02079d38(void *p0, void *p1);
extern void func_02079e64(void *p0, void *p1, Pair *pr);

void func_02079cc4(void *p0, void *p1, int p2)
{
    Pair pr;
    char *base;
    int i;

    pr.a = 0;
    pr.b = 0;
    base = func_02079350();
    for (i = 0; i < 8; i++) {
        func_020794d4(base + 0x2c * i, 3);
    }
    func_0209e474(&pr);
    if (func_0207a118(p0, &pr) != 0) {
        func_02079db8(p0, p1);
        if (p2 != 0) {
            MI_CpuCopy8(&pr, (char *) p0 + 0xc, 8);
        }
    } else {
        func_02079d38(p0, p1);
    }
    func_02079e64(p0, p1, &pr);
}
