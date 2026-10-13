/* func_ov147_0229a250 @ 0x0229a250, 0x2e bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov147_0229a594(int arg);
extern int func_ov147_0229a31c(int arg);
extern int func_ov147_0229a300(int arg);
extern int func_ov147_0229a374(int arg);
extern int func_ov147_0229a2f4(int arg);

int func_ov147_0229a250(int arg)
{
    int cond = func_ov147_0229a594(arg);
    int ret = func_ov147_0229a31c(arg);
    if (cond) {
        func_ov147_0229a374(func_ov147_0229a300(arg));
        return func_ov147_0229a2f4(arg);
    }
    return ret;
}
