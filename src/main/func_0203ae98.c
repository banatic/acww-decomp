/* func_0203ae98 @ 0x0203ae98, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0203c0ac(unsigned int, unsigned int);

extern unsigned char data_021c67a4[];

void func_0203ae98(void)
{
    unsigned int *ptr;
    unsigned int value;

    ptr = (unsigned int *) data_021c67a4;
    value = *ptr;
    func_0203c0ac(value, 4);
}
