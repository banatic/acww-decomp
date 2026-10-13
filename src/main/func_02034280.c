/* func_02034280 @ 0x02034280, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02034280(unsigned char *dst, unsigned char *src)
{
    dst[0] = src[0];
    *(int *) (dst + 4) = *(int *) (src + 4);
}
