/* func_02080814 @ 0x02080814, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0208150c(unsigned int);
extern int func_02003648(unsigned char *);
extern int func_02082500(int);

int func_02080814(unsigned int object)
{
    int result;

    result = func_02082500((int) func_02003648((unsigned char *) func_0208150c(object)));
    if (result != 0) {
        result += 0x3a;
    } else {
        result = 0;
    }
    return result;
}
