/* activity_vars: 6 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a13dc @ 0x020a13dc, 0xc bytes, Thumb
 * func_020a13d0 @ 0x020a13d0, 0xc bytes, Thumb
 * func_020a13c4 @ 0x020a13c4, 0xc bytes, Thumb
 * func_020a13b8 @ 0x020a13b8, 0xc bytes, Thumb
 * func_020a13ac @ 0x020a13ac, 0xc bytes, Thumb
 * func_020a13a0 @ 0x020a13a0, 0xc bytes, Thumb
 */

extern int data_021f3c34;
extern unsigned char data_021f3c1c;
extern int data_021f3c24;
extern unsigned char data_021f3c08;

void func_020a13dc(int arg0)
{
    data_021f3c34 = arg0;
}

unsigned char func_020a13d0(void)
{
    return data_021f3c1c;
}

void func_020a13c4(unsigned long value)
{
    data_021f3c1c = value;
}

int func_020a13b8(void)
{
    return data_021f3c24;
}

unsigned char func_020a13ac(void)
{
    return data_021f3c08;
}

void func_020a13a0(void)
{
    (*(volatile unsigned char *) &data_021f3c08) = 1;
}
