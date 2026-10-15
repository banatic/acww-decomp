/* func_ov105_0229f1d0 @ 0x0229f1d0, 0x68 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229c340(void *arg, int a);
extern void func_0206fc4c(int a);
extern int func_020984e8(void);
extern int func_020989e0(int object);
extern void *func_02097f58(int a, int b);
extern int func_02066830(void *dst, void *src);
extern void func_020ee470(void *arg);

int func_ov105_0229f1d0(void *arg)
{
    int res;
    int i;
    char *src;
    char *base;

    if (func_ov105_0229c340(arg, 0x1000) == 0) {
        func_0206fc4c(0);
    } else {
        func_0206fc4c(1);
        res = func_020989e0(func_020984e8());
        if (res != 0) {
            src = func_02097f58(res, 0);
            i = 0;
            base = (char *) arg + 0x2db8;
            for (; i < 50; i++) {
                func_02066830(src, base + i * 0x100);
                src += 0x100;
            }
        }
    }
    func_020ee470(arg);
    return 1;
}
