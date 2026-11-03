/* event_kinds_2: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203e7f0 @ 0x0203e7f0, 0x22 bytes, Thumb
 * func_0203e7d4 @ 0x0203e7d4, 0x1c bytes, Thumb
 */

extern int func_02095f28(void);
extern int func_02095f08(int);
extern void func_0203e358(void);
extern int func_02095d2c(void);
extern void func_0203e34c(void);

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

int func_0203e7d4(void)
{
    if (func_02095d2c() == 0) {
        return 0;
    }
    func_0203e34c();
    return 1;
}
