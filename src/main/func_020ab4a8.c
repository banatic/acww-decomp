/* func_020ab4a8 @ 0x020ab4a8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020ab4a8(void *r0)
{
    unsigned int *base = (unsigned int *) r0;
    unsigned int value;
    unsigned int result;

    value = *(unsigned int *) ((unsigned char *) base + 0x2d0);
    result = value - 1;
    *(unsigned int *) ((unsigned char *) base + 0x2d4) = result;
}
