/* heap_17: 6 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020edb7c @ 0x020edb7c, 0x1c bytes, ARM
 * func_020edb60 @ 0x020edb60, 0x1c bytes, ARM
 * func_020edb54 @ 0x020edb54, 0xc bytes, ARM
 * func_020edb48 @ 0x020edb48, 0xc bytes, ARM
 * func_020edb3c @ 0x020edb3c, 0xc bytes, ARM
 * func_020edb30 @ 0x020edb30, 0xc bytes, ARM
 */

extern unsigned int data_021fbe94;
extern unsigned int func_020e9948(unsigned int, unsigned int);
extern void func_020e993c(int a, int b);

unsigned int func_020edb7c(unsigned int arg)
{
    return func_020e9948(data_021fbe94, arg);
}

void func_020edb60(int a)
{
    func_020e993c((*(int *) &data_021fbe94), a);
}

unsigned int func_020edb54(unsigned int argument0)
{
    return func_020edb7c(argument0);
}

void func_020edb48(unsigned int argument0)
{
    func_020edb7c(argument0);
}

void func_020edb3c(int argument0)
{
    func_020edb60(argument0);
}

void func_020edb30(int argument0)
{
    func_020edb60(argument0);
}
