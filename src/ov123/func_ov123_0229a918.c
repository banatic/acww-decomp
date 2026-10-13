/* func_ov123_0229a918 @ 0x0229a918, 0x70 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern int *func_ov123_02299d9c(void *, void *);
extern int func_ov123_0229a63c(void *, int, int, void *);
extern int data_ov123_0229cb2c[];

void func_ov123_0229a918(void *a, void *b)
{
    int *p;
    int *q;
    int i;
    int init;
    int o;

    p = func_ov123_02299d9c(a, b);
    init = 0;
    o = 0;
    while (o < 2) {
        q = data_ov123_0229cb2c;
        i = init;
        while (i < 16) {
            p[0] = func_ov123_0229a63c(a, p[0], q[0], b);
            p[1] = func_ov123_0229a63c(a, p[1], q[1], b);
            p[2] = func_ov123_0229a63c(a, p[2], q[0], b);
            p[3] = func_ov123_0229a63c(a, p[3], q[1], b);
            p += 4;
            q += 2;
            i++;
        }
        o++;
    }
}
