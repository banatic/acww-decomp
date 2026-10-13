/* func_ov113_02299da4 @ 0x02299da4, 0x12 bytes, Thumb, module ov113
 * mwccarm 1.2/base -O4,s
 */

int func_ov113_02299da4(unsigned char *ptr, unsigned short mask)
{
    if (*(unsigned short *) (ptr + 0x98) & mask) {
        return 1;
    }
    return 0;
}
