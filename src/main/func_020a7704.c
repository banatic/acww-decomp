/* func_020a7704 @ 0x020a7704, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020a7704(int *src, int *dst1, unsigned char *dst2)
{
    *dst1 = *src;
    *dst2 = *(unsigned char *) ((char *) src + 4);
}
