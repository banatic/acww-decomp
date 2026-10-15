/* func_ov112_022a0258 @ 0x022a0258, 0x44 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov112_0229f900(void *);
extern void func_ov112_0229f89c(void *);
extern void func_ov095_0229b3ec(void *);
extern int func_ov112_022a029c(void *, int, int);
extern void func_ov112_0229fd20(void *);
extern void func_ov112_0229f668(void *);

int func_ov112_022a0258(void *param1, int param2)
{
    int result;

    if (func_ov112_0229f900(param1)) {
        func_ov112_0229f89c(param1);
        func_ov095_0229b3ec((char *) param1 + 0x384);
    }
    result = func_ov112_022a029c(param1, param2, 1);
    func_ov112_0229fd20(param1);
    func_ov112_0229f668(param1);
    return result;
}
