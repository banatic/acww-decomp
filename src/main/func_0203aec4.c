/* func_0203aec4 @ 0x0203aec4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0203c0ac(unsigned int, int);

extern unsigned char data_021c67a4[];

void func_0203aec4(void)
{
    unsigned int *ptr;
    unsigned int value;

    ptr = (unsigned int *) data_021c67a4;
    value = *ptr;
    func_0203c0ac(value, 3);
}
