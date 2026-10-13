/* func_ov120_0229b14c @ 0x0229b14c, 0x1a bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_ov120_0229b168(void);

unsigned int func_ov120_0229b14c(void)
{
    unsigned int v = func_ov120_0229b168();
    unsigned int result;

    if (v <= 6) {
        result = 0;
    } else {
        result = (v - 6) << 4;
    }

    return result;
}
