/* func_020faba4 @ 0x020faba4, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int (*NNS_GfdDefaultFuncAllocTexVram)(int, int, int);

int func_020faba4(int a, int b)
{
    return (NNS_GfdDefaultFuncAllocTexVram(a, b, 0) & 0xffff) << 3;
}
