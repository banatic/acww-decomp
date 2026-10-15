/* func_02080890 @ 0x02080890, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(unsigned int);
extern int func_02003648(unsigned char *);
extern int func_02082500(int);

int func_02080890(unsigned int object)
{
    int r4 = 0;
    int r0;

    r0 = func_02082500((int) func_02003648((unsigned char *) func_0208150c(object)));
    if (r0 != 0) {
        r4 = r0;
    }
    return r4;
}
