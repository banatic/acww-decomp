/* func_020100e8 @ 0x020100e8, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

int func_020100e8(void *base, unsigned short *src, unsigned char a, unsigned char b, unsigned char c)
{
    if (*(int *) ((char *) base + 0xc94) == 2) {
        *(int *) ((char *) base + 0xc94) = 0;
        *(unsigned short *) ((char *) base + 0xc98) = *src;
        *(unsigned char *) ((char *) base + 0xc9a) = a;
        *(unsigned char *) ((char *) base + 0xc9b) = b;
        *(unsigned char *) ((char *) base + 0xc9c) = c;
        return 1;
    } else {
        return 0;
    }
}
