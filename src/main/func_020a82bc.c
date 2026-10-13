/* func_020a82bc @ 0x020a82bc, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020a82bc(void *r0, const void *r1)
{
    unsigned char *dst = (unsigned char *) r0;
    const unsigned char *src = (const unsigned char *) r1;

    *(unsigned int *) dst = *(const unsigned int *) src;
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    dst[7] = src[7];
    dst[8] = src[8];
    dst[9] = src[9];
    dst[10] = src[10];
    dst[11] = src[11];
}
