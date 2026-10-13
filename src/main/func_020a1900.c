/* func_020a1900 @ 0x020a1900, 0xc bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021f3c38[];

void func_020a1900(void)
{
    unsigned int *r0;
    unsigned int r1;

    r1 = 0x13;
    r0 = (unsigned int *) data_021f3c38;
    *r0 = r1;
}
