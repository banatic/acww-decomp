/* func_0203e7f0 @ 0x0203e7f0, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095f28(void);
extern int func_02095f08(int);
extern void func_0203e358(void);

int func_0203e7f0(void)
{
    int result;

    if (func_02095f28() == 0) {
        result = 0;
    } else {
        func_02095f08(1);
        func_0203e358();
        result = 1;
    }
    return result;
}
