/* func_ov111_0229fa50 @ 0x0229fa50, 0x26 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229fa78(void *argument0);
extern void func_ov111_0229f524(int);
extern void func_ov111_0229fd08(int);
extern void func_ov111_0229f854(void);

void func_ov111_0229fa50(int param)
{
    if (func_ov111_0229fa78((void *) param)) {
        func_ov111_0229f524(param);
        func_ov111_0229fd08(param);
    } else {
        // clang-format off
        asm {
            mov r0, param
        }
        // clang-format on
        func_ov111_0229f854();
    }
}
