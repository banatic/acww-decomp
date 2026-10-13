/* func_ov096_0229f290 @ 0x0229f290, 0x90 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(char *, int);
extern int func_ov096_0229f7ac(char *, int);
extern int func_ov096_0229f820(char *, int);
extern int func_ov096_0229f548(char *, int);
extern int func_ov096_0229f810(char *, int);
extern int func_ov096_0229f800(char *, int);
extern int func_ov094_0229aba4(char *, int);
extern int func_ov094_0229b384(char *, int);
extern int func_ov090_022990b8(int);

int func_ov096_0229f290(char *a, int b)
{
    int ret;
    if (func_ov096_0229f830(a, b) != 0) {
        ret = func_ov096_0229f7ac(a, b);
        return func_ov094_0229aba4(a + 0x358, ret);
    }
    if (func_ov096_0229f820(a, b) != 0) {
        ret = func_ov096_0229f548(a, b);
        return func_ov094_0229b384(a + 0xdb8, ret);
    }
    if (func_ov096_0229f810(a, b) != 0) {
        b -= 0x19;
        return func_ov090_022990b8(b) - 8;
    }
    if (func_ov096_0229f800(a, b) != 0) {
        ret = func_ov096_0229f7ac(a, b);
        return func_ov094_0229aba4(a + 0x358, ret);
    }
    return 0;
}
