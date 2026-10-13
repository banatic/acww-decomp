/* func_0207f2c4 @ 0x0207f2c4, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void);
extern int func_02003648(void);
extern int func_02082500(void);

int func_0207f2c4(void)
{
    int result;
    int temp;

    func_0208150c();
    func_02003648();
    temp = func_02082500();

    if (temp != 0) {
        result = *(unsigned char *) (temp + 0x4d);
    } else {
        result = 0;
    }

    return result;
}
