/* func_ov004_022109cc @ 0x022109cc, 0x18 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_022109cc(void);
extern int func_0203efdc(void);

int func_ov004_022109cc(void)
{
    int result;
    if (func_0203efdc() != 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}
