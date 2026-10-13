/* func_020808ec @ 0x020808ec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208150c(void);
extern void func_02003648(void);
extern int func_02082500(void);

int func_020808ec(void)
{
    int r4;
    int r0;

    r4 = 0x21;
    func_0208150c();
    func_02003648();
    r0 = func_02082500();
    if (r0 != 0) {
        r0 += 0x4c;
        r4 = *(unsigned char *) r0;
    }
    return r4;
}
