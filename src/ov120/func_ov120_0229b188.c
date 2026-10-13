/* func_ov120_0229b188 @ 0x0229b188, 0x28 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov120_0229a448(char *p, int flag);

char *func_ov120_0229b188(char *p)
{
    if (func_ov120_0229a448(p, 1) != 0) {
        return p + 0x272D;
    } else {
        return p + 0x2720;
    }
}
