/* func_ov003_022211bc @ 0x022211bc, 0x6c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(void);
extern void func_0204f818(int *a, int *b, int c);
extern int func_0204eda8(int a, int b, int c);
extern int func_ov003_0222139c(void *a, int b, int *c, int *d, int e, int f, int g, int h);
extern int data_ov003_0223cfe4;

int func_ov003_022211bc(int p0, int p1)
{
    int r6;
    int a, b;
    int x;
    int s1[2];
    int s2[3];

    r6 = func_0204e414();
    if (r6 == 0) {
        return 0;
    }

    a = 0;
    b = 0;
    func_0204f818(&a, &b, p1);

    x = (func_0204eda8(r6, a, b) == 0) ? 0xfc : 0xfd;

    s2[0] = 0;
    s2[1] = 0;
    s2[2] = 0;
    s1[0] = a;
    s1[1] = b;

    return func_ov003_0222139c((void *) &data_ov003_0223cfe4, p0, s1, s2, 3, x, 0, 0);
}
