/* func_0203e68c @ 0x0203e68c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095d04(void);
extern int func_ov004_0222bfb4(void);

int func_0203e68c(unsigned char *arg0)
{
    int result;

    if (func_02095d04() == 0) {
        result = 0;
    } else {
        if (func_ov004_0222bfb4() == 0) {
            result = 0;
        } else {
            arg0[0x16] = 5;
            result = 1;
        }
    }
    return result;
}
