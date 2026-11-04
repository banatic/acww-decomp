/* particle_system_3: 3 functions, module autoload_2
 * mwccarm 1.2/base -O4,s
 * func_020fabdc @ 0x020fabdc, 0xc bytes, ARM
 * func_020faba4 @ 0x020faba4, 0x38 bytes, ARM
 * func_020fab6c @ 0x020fab6c, 0x38 bytes, ARM
 */

extern void func_020fded0(void *argument0, void *argument1);
extern int (*NNS_GfdDefaultFuncAllocTexVram)(int, int, int);
extern int (*NNS_GfdDefaultFuncAllocPlttVram)(int, int, int);

void func_020fabdc(void *argument0, void *argument1)
{
    func_020fded0(argument0, argument1);
}

int func_020faba4(int a, int b)
{
    return (NNS_GfdDefaultFuncAllocTexVram(a, b, 0) & 0xffff) << 3;
}

int func_020fab6c(int a, int b)
{
    return (NNS_GfdDefaultFuncAllocPlttVram(a, b, 0) & 0xffff) << 3;
}
