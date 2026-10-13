/* func_0209a8c4 @ 0x0209a8c4, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209ad9c(void *param, int mode);
extern void *func_0209b4d4(int value);
extern int func_0209bd44(void *p);
extern int func_0209bc40(void *p);
extern int func_0209bba0(void *p);
extern void func_0209bb90(void *p, int value);

void func_0209a8c4(void *param)
{
    void *p;
    p = func_0209b4d4(func_0209ad9c(param, 0));
    if (func_0209bd44(p) != 0 && func_0209bc40(p) == 0x12 && func_0209bba0(p) == 0) {
        func_0209bb90(p, 1);
    }
}
