/* func_ov119_0229ad84 @ 0x0229ad84, 0x3e bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern char *func_ov119_0229ae50(void);
extern int func_02077c3c(void *ptr);
extern int func_02077e50(int arg);

int func_ov119_0229ad84(void)
{
    char *ptr = func_ov119_0229ae50();
    int found_zero = 0;
    int i;
    for (i = 0; i < 32; i++) {
        if (func_02077e50(func_02077c3c(ptr + i * 0x24)) != 0) {
            if (found_zero) {
                return 1;
            }
        } else {
            found_zero = 1;
        }
    }
    return 0;
}
