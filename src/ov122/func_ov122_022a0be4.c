/* func_ov122_022a0be4 @ 0x022a0be4, 0x108 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229ba44(void *, int, int);
extern void func_ov122_022a15b8(void *, int, int);
extern int func_ov095_0229bebc(void *, int);
extern int func_ov122_022a1030(void *, int);
extern int func_ov122_022a0f78(void *, int);
extern void func_ov122_0229f388(void *);
extern void func_ov122_022a0df8(void *);
extern void func_ov122_022a0dec(void *);
extern void func_ov122_022a0d84(void *);
extern void func_ov122_022a0cec(void *);
extern int func_ov122_022a0e4c(void *, unsigned short);

int func_ov122_022a0be4(char *a, int b)
{
    int ret = 1;
    int t;

    t = func_ov095_0229ba44(a + 0xc0, b, 6);
    if (t != 0) {
        func_ov122_022a15b8(a, 0, ret);
        return t;
    }
    if (func_ov095_0229bebc(a + 0xc0, b)) {
        switch (b) {
            case 0x100:
                func_ov122_022a1030(a, ret);
                break;
            case 0x103:
            case 0x104:
            case 0x105:
                if (func_ov122_022a0f78(a, b) == 0) {
                    func_ov122_0229f388(a);
                }
                ret = 2;
                break;
            case 0x113:
                func_ov122_022a0df8(a);
                ret = 3;
                break;
            case 0x114:
                func_ov122_022a0dec(a);
                ret = 3;
                break;
            case 0x118:
                func_ov122_022a0d84(a);
                ret = 2;
                break;
            case 0x119:
                func_ov122_022a0cec(a);
                ret = 2;
                break;
        }
    } else {
        if (func_ov122_022a0e4c(a, (unsigned short) b) == 0) {
            func_ov122_0229f388(a);
        }
        if (b == 0xa) {
            ret = 2;
        }
    }
    return ret;
}
