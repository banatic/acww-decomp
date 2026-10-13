/* func_020a7778 @ 0x020a7778, 0x1a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020a7778(unsigned char *src, unsigned char *d1, unsigned char *d2, unsigned char *d3, unsigned int *d4)
{
    *d1 = src[0];
    *d2 = src[1];
    *d3 = src[2];
    *d4 = *(unsigned int *) (src + 4);
}
