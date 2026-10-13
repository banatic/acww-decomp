/* func_02080890 @ 0x02080890, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void);
extern int func_02003648(void);
extern int func_02082500(void);

int func_02080890(void)
{
    int r4 = 0;
    int r0;

    func_0208150c();
    func_02003648();
    r0 = func_02082500();
    if (r0 != 0) {
        r4 = r0;
    }
    return r4;
}
