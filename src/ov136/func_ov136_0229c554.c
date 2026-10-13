/* func_ov136_0229c554 @ 0x0229c554, 0x10 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

void func_ov136_0229c554(char *base, unsigned short mask)
{
    *(unsigned short *) (base + 0x2b74) &= ~mask;
}
