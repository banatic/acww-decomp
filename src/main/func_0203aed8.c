/* func_0203aed8 @ 0x0203aed8, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0203c0ac(unsigned int);

extern unsigned char data_021c67a4[];

void func_0203aed8(void)
{
    unsigned int *r0;
    unsigned int r1;
    unsigned int r3;

    r0 = (unsigned int *) data_021c67a4;
    r0 = (unsigned int *) *r0;
    r1 = 0x13;
    r3 = (unsigned int) func_0203c0ac;
    ((void (*)(unsigned int, unsigned int)) r3)((unsigned int) r0, r1);
}
