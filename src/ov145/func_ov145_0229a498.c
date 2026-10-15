/* func_ov145_0229a498 @ 0x0229a498, 0x4c bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;

extern void func_ov145_0229a184(char *param);
extern int func_ov145_02299f30(char *param);
extern int func_ov145_02299eec(char *param);
extern int func_ov145_0229a210(char *param);
extern void func_ov002_0220a0b4(char *ptr, int a, int b);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov145_0229a498(char *param)
{
    if (data_021fbe40 & 1) {
        int res1, res2;
        func_ov145_0229a184(param);
        res1 = func_ov145_02299f30(param);
        res2 = func_ov145_02299eec(param);
        func_ov002_0220a0b4(param + 0xc8, res1, res2);
    } else {
        func_ov145_0229a210(param);
        func_ov002_02208098((void *) (param), 5);
    }
}
