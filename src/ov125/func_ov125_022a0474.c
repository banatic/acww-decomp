/* func_ov125_022a0474 @ 0x022a0474, 0x2c bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_022091cc(void *);
extern int func_ov002_02207d5c(void *);
extern void func_ov125_0229fd3c(void *);

void func_ov125_022a0474(void *arg0)
{
    func_ov002_022091cc((char *) arg0 + 0x180);
    if (func_ov002_02207d5c((char *) arg0 + 0x574)) {
        func_ov125_0229fd3c(arg0);
    }
}
