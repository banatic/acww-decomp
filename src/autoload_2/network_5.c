/* network_5: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020eb6ac @ 0x020eb6ac, 0xc bytes, ARM
 * func_020eb6a0 @ 0x020eb6a0, 0xc bytes, ARM
 * func_020eb694 @ 0x020eb694, 0xc bytes, ARM
 */

extern int DWCi_Acc_IsAuthentic(int data);
extern void func_0210111c(void *source, void *destination);
extern unsigned long long func_0210118c(const void *data);

int func_020eb6ac(int data)
{
    return DWCi_Acc_IsAuthentic(data);
}

void func_020eb6a0(void *source, void *destination)
{
    func_0210111c(source, destination);
}

unsigned long long func_020eb694(const void *data)
{
    return func_0210118c(data);
}
