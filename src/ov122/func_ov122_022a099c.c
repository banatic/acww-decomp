/* func_ov122_022a099c @ 0x022a099c, 0x58 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov122_0229f170(void *);
extern int func_ov095_0229bf0c(void *);
extern int func_ov095_0229c548(void *);
extern int func_ov095_0229c448(void *, int, int);
extern int func_ov122_022a0be4(void *, int);
extern void func_ov095_0229c8e4(void *, int);

void func_ov122_022a099c(void *arg)
{
    int a;

    if ((data_021fbe40 & 1) == 0) {
        func_ov122_0229f170(arg);
        return;
    }
    if (func_ov095_0229bf0c((char *) arg + 0xc0) != 0) {
        a = func_ov095_0229c548((char *) arg + 0xc0);
        func_ov122_022a0be4(arg, func_ov095_0229c448((char *) arg + 0xc0, a, 9));
        func_ov095_0229c8e4((char *) arg + 0xc0, a);
    }
}
