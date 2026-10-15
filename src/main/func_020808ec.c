/* func_020808ec @ 0x020808ec, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int);
extern int func_02003648(unsigned char *);
extern int func_02082500(int);

int func_020808ec(unsigned int object)
{
    int r4;
    int r0;

    r4 = 0x21;
    r0 = func_02082500((int) func_02003648((unsigned char *) func_0208150c(object)));
    if (r0 != 0) {
        r0 += 0x4c;
        r4 = *(unsigned char *) r0;
    }
    return r4;
}
