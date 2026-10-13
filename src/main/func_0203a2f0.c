/* func_0203a2f0 @ 0x0203a2f0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020da610[];
extern unsigned char data_020da6c4[];

void func_0203a2f0(unsigned int *mem, unsigned int a, unsigned int b)
{
    *(volatile unsigned int *) mem = (unsigned int) data_020da6c4;
    *(volatile unsigned int *) mem = (unsigned int) data_020da610;
    mem[1] = a;
    mem[2] = b;
}
