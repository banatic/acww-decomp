/* villager_data: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020808b0 @ 0x020808b0, 0x20 bytes, Thumb
 * func_02080890 @ 0x02080890, 0x1e bytes, Thumb
 * func_02080864 @ 0x02080864, 0x2c bytes, Thumb
 * func_02080834 @ 0x02080834, 0x30 bytes, Thumb
 * func_02080814 @ 0x02080814, 0x20 bytes, Thumb
 */

extern int func_0208150c(unsigned int);
extern int func_02003648(unsigned char *);
extern int func_02082500(int);
extern int func_0207dd10(int a);
extern int func_0209b6c0(int a, unsigned char b, unsigned char c);

int func_020808b0(unsigned int object)
{
    int r4;
    int r0;

    r4 = 0;
    r0 = func_02082500((int) func_02003648((unsigned char *) func_0208150c(object)));
    if (r0 != 0) {
        r4 = r0 + 0x29;
    }
    return r4;
}

int func_02080890(unsigned int object)
{
    int r4 = 0;
    int r0;

    r0 = func_02082500((int) func_02003648((unsigned char *) func_0208150c(object)));
    if (r0 != 0) {
        r4 = r0;
    }
    return r4;
}

int func_02080864(int param1, unsigned int param2)
{
    int ret = 0;
    if (param2 < 6u) {
        int tmp = func_02082500(func_02003648((unsigned char *) (func_0208150c(param1))));
        if (tmp != 0) {
            ret = tmp + 26 + param2 * 2;
        }
    }
    return ret;
}

int func_02080834(int a, int b)
{
    int tmp;
    unsigned char *p;

    tmp = func_0207dd10(a);
    p = (unsigned char *) func_02080864(a, tmp);
    if (p != 0) {
        return func_0209b6c0(b, p[0], p[1]);
    }
    return 0;
}

int func_02080814(unsigned int object)
{
    int result;

    result = func_02082500((int) func_02003648((unsigned char *) (unsigned int) func_0208150c(object)));
    if (result != 0) {
        result += 0x3a;
    } else {
        result = 0;
    }
    return result;
}
