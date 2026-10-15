/* func_020fab6c @ 0x020fab6c, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int (*NNS_GfdDefaultFuncAllocPlttVram)(int, int, int);

int func_020fab6c(int a, int b)
{
    return (NNS_GfdDefaultFuncAllocPlttVram(a, b, 0) & 0xffff) << 3;
}
