/* func_0207f2c4 @ 0x0207f2c4, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(unsigned int);
extern int func_02003648(unsigned char *);
extern int func_02082500(int);

int func_0207f2c4(int result)
{
    int temp;

    temp = func_02082500((int) func_02003648((unsigned char *) func_0208150c(result)));

    if (temp != 0) {
        result = *(unsigned char *) (temp + 0x4d);
    } else {
        result = 0;
    }

    return result;
}
