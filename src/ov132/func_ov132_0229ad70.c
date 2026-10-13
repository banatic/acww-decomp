/* func_ov132_0229ad70 @ 0x0229ad70, 0x18 bytes, Thumb, module ov132
 * mwccarm 1.2/base -O4,s
 */

int func_ov132_0229ad70(char *a, int b)
{
    if (*(unsigned short *) (a + 0x1500) & b) {
        return 1;
    }
    return 0;
}
