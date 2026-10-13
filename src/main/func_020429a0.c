/* func_020429a0 @ 0x020429a0, 0x66 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020429a0(void *unused, unsigned char *dst, const unsigned char *src, int count)
{
    int i;
    i = 0;
    while (i < count) {
        unsigned int b7 = src[7] << 7;
        unsigned int b6 = src[6] << 6;
        unsigned int b5 = src[5] << 5;
        unsigned int b4 = src[4] << 4;
        unsigned int b3 = src[3] << 3;
        unsigned int b2 = src[2] << 2;
        unsigned int b0 = src[0];
        unsigned int b1 = src[1] << 1;
        *dst = (unsigned char) (b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7);
        src += 8;
        dst++;
        i++;
    }
}
