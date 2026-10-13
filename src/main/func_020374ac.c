/* func_020374ac @ 0x020374ac, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_020374ac(void *r0)
{
    unsigned short *p16 = (unsigned short *) ((char *) r0 + 4);
    unsigned char *p8 = (unsigned char *) r0;
    unsigned int *p32 = (unsigned int *) r0;

    p32[0] = 0x25;
    *p16 = 0xffff;
    p32[2] = 0;
    p32[3] = 0;
    p8[0x10] = 0;
    p8[0x11] = 0;
    p8[0x12] = 0;
    p8[0x13] = 0;
    p8[0x14] = 0;
    p32[6] = 0;
}
