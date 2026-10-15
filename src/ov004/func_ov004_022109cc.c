/* func_ov004_022109cc @ 0x022109cc, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022109cc(int result);
extern int func_0203efdc(char *arg0);

int func_ov004_022109cc(int result)
{
    if (func_0203efdc((char *) result) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
