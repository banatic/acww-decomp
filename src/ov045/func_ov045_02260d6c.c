/* func_ov045_02260d6c @ 0x02260d6c, 0x30 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *ptr);
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);
extern void func_ov045_02260e50(void *ptr, int n);

int func_ov045_02260d6c(void *param)
{
    if (func_02014868((char *) param + 0x618) == 0) {
        func_020b6098(func_020b5e10(), 0);
        func_ov045_02260e50(param, 2);
    }
    return 1;
}
