/* func_020963f8 @ 0x020963f8, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

unsigned char func_020963f8(unsigned char *ptr, int idx)
{
    if (idx < 4) {
        return *(unsigned char *) (ptr + idx + 16);
    }
    return 7;
}
