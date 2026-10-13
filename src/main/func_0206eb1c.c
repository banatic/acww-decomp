/* func_0206eb1c @ 0x0206eb1c, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_0206eb1c(unsigned short *a, unsigned short *b)
{
    int i;
    a[0] = 0;
    for (i = 1; i < 16; i++) {
        unsigned short c = a[i];
        unsigned short r = c & 0x1f;
        unsigned short g = (c & 0x3e0) >> 5;
        unsigned short bl = (c & 0x7c00) >> 10;
        r = (r + 0x1f) >> 1;
        g = (g + 0x1f) >> 1;
        bl = (bl + 0x1f) >> 1;
        b[i] = (unsigned short) (r | (g << 5) | (bl << 10));
    }
}
