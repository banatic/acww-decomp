/* func_0209b878 @ 0x0209b878, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_0209b878(unsigned char *param0, unsigned int param1)
{
    if (param1 < 3) {
        if ((param0[0x30] >> param1) & 1) {
            return 1;
        }
    }
    return 0;
}
