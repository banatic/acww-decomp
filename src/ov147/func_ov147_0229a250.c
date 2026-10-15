/* func_ov147_0229a250 @ 0x0229a250, 0x2e bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov147_0229a594(void *object);
extern void func_ov147_0229a31c(void *object);
extern void func_ov147_0229a300(void *object);
extern void func_ov147_0229a374(void);
extern void func_ov147_0229a2f4(int *arg);

void func_ov147_0229a250(int *arg)
{
    int r = func_ov147_0229a594(arg);
    func_ov147_0229a31c(arg);
    if (r != 0) {
        func_ov147_0229a300(arg);
        func_ov147_0229a374();
        func_ov147_0229a2f4(arg);
    }
}
