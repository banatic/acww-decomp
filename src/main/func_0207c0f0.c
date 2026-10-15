/* func_0207c0f0 @ 0x0207c0f0, 0x6e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0207c160(int);
extern int func_0207cec0(int, int);
extern unsigned int func_0207f1c8(unsigned int object);
extern int func_0209b5ec(void *);
extern int func_0209bfec(int);
extern int func_0209e3ac(int, int, int);
extern int func_0209e380(int, int);

int func_0207c0f0(int a, int b)
{
    int forwarded_value;

    int res1, t, s, r2;

    res1 = func_0207c160(a);
    if ((forwarded_value = (int) func_0207cec0(a, res1)) == 0) {
        goto ret_minus1;
    }
    s = func_0209b5ec((void *) func_0207f1c8((unsigned int) forwarded_value));
    t = func_0209e3ac(b, func_0209bfec(s), 0x3f);
    r2 = 0;
    if (t == 1) {
        r2 = func_0209e380(func_0209bfec(s), b);
    } else if (t == -1) {
        r2 = func_0209e380(b, func_0209bfec(s));
    }
    if (r2 < 2) {
        goto ret_minus1;
    }
    return res1;

ret_minus1:
    return -1;
}
