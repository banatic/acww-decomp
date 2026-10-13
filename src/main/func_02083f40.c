/* func_02083f40 @ 0x02083f40, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern int func_0209967c(void);
extern int func_020887c0(int a, int b);

int func_02083f40(void)
{
    int result = 0;
    if (func_020984e8() != 0) {
        if (func_020887c0(func_0209967c(), 0x18) == 0) {
            result = 1;
        }
    }
    return result;
}
