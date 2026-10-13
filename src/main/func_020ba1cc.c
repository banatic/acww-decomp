/* func_020ba1cc @ 0x020ba1cc, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e5954[];

void func_020ba1cc(unsigned int *r0)
{
    unsigned int *p = r0;
    unsigned char *b = (unsigned char *) r0;
    unsigned int zero = 0;

    p[1] = zero;
    p[2] = zero;
    b[0xc] = 0xff;
    p[0] = (unsigned int) data_020e5954;
    b[0xd] = zero;
    b[0xe] = 0xa;
    b[0xf] = 1;
}
