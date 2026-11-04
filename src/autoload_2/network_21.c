/* network_21: 5 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020edb14 @ 0x020edb14, 0x1c bytes, ARM
 * func_020edaf0 @ 0x020edaf0, 0x24 bytes, ARM
 * func_020edacc @ 0x020edacc, 0x24 bytes, ARM
 * func_020edab8 @ 0x020edab8, 0x14 bytes, ARM
 * func_020edaa8 @ 0x020edaa8, 0x10 bytes, ARM
 */

extern void func_020ecde8(void);
extern void func_0206e6b0(void);
extern int (*data_021fbf08)(int a0, int a1);
extern int (*OS_PutString)(int);

void func_020edb14(void)
{
    func_020ecde8();
    func_0206e6b0();
}

int func_020edaf0(int a0, int a1)
{
    return data_021fbf08(a0, a1);
}

int func_020edacc(int arg)
{
    return OS_PutString(arg);
}

int func_020edab8(int unused, int a, int b)
{
    return func_020edaf0(a, b);
}

void func_020edaa8(int a, int b)
{
    func_020edacc(b);
}
