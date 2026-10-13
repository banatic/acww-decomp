/* func_0209b1f0 @ 0x0209b1f0, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_0209b218(int a, int b);

unsigned char func_0209b1f0(int a, int b)
{
    unsigned char res;
    res = func_0209b218(a, b);
    if (((b >> 2) & 1) && ((b >> 3) & 1)) {
        res--;
    }
    return res;
}
