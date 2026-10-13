/* func_020789f4 @ 0x020789f4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020789f4(int *hi, int *lo, const unsigned char *byte)
{
    *hi = (*byte >> 4) & 0x0f;
    *lo = *byte & 0x0f;
}
