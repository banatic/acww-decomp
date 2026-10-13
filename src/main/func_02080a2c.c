/* func_02080a2c @ 0x02080a2c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void);
extern int func_02003648(void);
extern int func_02082500(void);

int func_02080a2c(void)
{
    int r4 = 0;
    int r0;

    func_0208150c();
    func_02003648();
    r0 = func_02082500();

    if (r0 != 0) {
        r4 = r0 + 0x26;
    }

    return r4;
}
