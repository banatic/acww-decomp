/* func_ov143_0229abcc @ 0x0229abcc, 0x1e bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov143_0229a16c(void *arg0);
extern void func_020ee470(int);

int func_ov143_0229abcc(int arg0)
{
    int result;

    if (func_ov143_0229a16c((void *) arg0) == 0) {
        result = 1;
    } else {
        func_020ee470(arg0);
        result = 1;
    }
    return result;
}
