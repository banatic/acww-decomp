/* func_02080814 @ 0x02080814, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(void);
extern void func_02003648(void);
extern int func_02082500(void);

int func_02080814(void)
{
    int result;

    func_0208150c();
    func_02003648();
    result = func_02082500();
    if (result != 0) {
        result += 0x3a;
    } else {
        result = 0;
    }
    return result;
}
