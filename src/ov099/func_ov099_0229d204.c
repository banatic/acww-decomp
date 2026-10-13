/* func_ov099_0229d204 @ 0x0229d204, 0x3c bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208e28(void *);
extern int func_0206fe54(int);
extern void func_ov099_0229c63c(void *);
extern void func_ov002_02208098(void *, int);

void func_ov099_0229d204(void *arg)
{
    int x = func_ov002_02208e28((char *) arg + 0x22d8);
    if (x != 0) {
        if (func_0206fe54(x) != 0) {
            func_ov099_0229c63c(arg);
            func_ov002_02208098(arg, 6);
        } else {
            func_ov002_02208098(arg, 2);
        }
    }
}
