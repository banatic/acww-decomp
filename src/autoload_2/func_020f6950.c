/* func_020f6950 @ 0x020f6950, 0x20 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

void func_020f6950(unsigned char *dst, const unsigned char *src)
{
    int i;
    for (i = 0; i < 16; i++) {
        *(dst + i + 0x28) = src[i];
    }
}
