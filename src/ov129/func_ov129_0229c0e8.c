/* func_ov129_0229c0e8 @ 0x0229c0e8, 0x30 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

void func_ov129_0229c0e8(unsigned char *p)
{
    int i;
    int j;
    unsigned char *q;
    q = p + 0x2f98;
    i = 0;
    j = i;
    do {
        if ((unsigned char) (*q + 0xfe) <= 1) {
            *q = j;
        }
        q++;
        i++;
    } while (i < 454);
}
