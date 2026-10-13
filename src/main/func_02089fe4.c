/* func_02089fe4 @ 0x02089fe4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02089fe4(void *r0)
{
    unsigned char *p = (unsigned char *) r0;
    unsigned int zero = 0;

    *(unsigned int *) (p + 0x38) = zero;
    *(unsigned int *) (p + 0x10) = zero;
    *(unsigned int *) (p + 0x14) = zero;
    *(unsigned int *) (p + 0x18) = zero;
    p[0x3c] = (unsigned char) zero;
    *(unsigned int *) (p + 0x2c) = zero;
    *(unsigned int *) (p + 0x28) = zero;
    p[0xe] = (unsigned char) zero;
    p[0xf] = 0xff;
}
