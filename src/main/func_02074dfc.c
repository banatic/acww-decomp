/* func_02074dfc @ 0x02074dfc, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02074e48(int);
extern char *func_02073d28(int, int);
extern void func_02077b3c(void *, int, int);
extern int func_020a6f64(int);
extern int func_020740b4(int);

int func_02074dfc(int arg)
{
    int result = 0;
    if (func_02074e48(arg)) {
        char *p;
        int t1, t2;
        p = func_02073d28(data_020ccf94, arg);
        func_02077b3c(p, result, 6);
        t1 = func_020a6f64(arg);
        t2 = func_020740b4(t1);
        p[1] = (char) ((t1 & 7) | ((t2 << 4) & 0xf0));
        result += 2;
    }
    return result;
}
