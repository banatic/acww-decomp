/* func_0203cc1c @ 0x0203cc1c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203cbf4(void);
extern int func_0203cc14(void);

int func_0203cc1c(void)
{
    int a;
    int b;
    int result;

    a = func_0203cbf4();
    b = func_0203cc14();
    if (a == b) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
