/* heap: 4 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020e98f4 @ 0x020e98f4, 0x24 bytes, ARM
 * func_020e98d4 @ 0x020e98d4, 0x20 bytes, ARM
 * func_020e98b4 @ 0x020e98b4, 0x20 bytes, ARM
 * func_020e9898 @ 0x020e9898, 0x1c bytes, ARM
 */

extern int data_021fbe94;
int func_020e9ed4(int, int, int);
extern void func_020e9c48(int a, int b);

int func_020e98f4(int a, int b)
{
    return func_020e9ed4(data_021fbe94, a, b);
}

int func_020e98d4(unsigned int param)
{
    return func_020e9ed4((*(unsigned int *) &data_021fbe94), param, -4);
}

int func_020e98b4(void *param)
{
    return func_020e9ed4((int) ((*(void **) &data_021fbe94)), (int) param, 4);
}

void func_020e9898(int arg)
{
    func_020e9c48(data_021fbe94, arg);
}
