/* func_0204927c @ 0x0204927c, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f800(int *a, int *b, int c, int d, int e, int f);
extern void func_02049384(int a, int b, int c, int d);

void func_0204927c(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
    int local0, local1;
    func_0204f800(&local0, &local1, arg3, arg4, arg5, arg6);
    func_02049384(arg1 + ((arg5 >> 3) & 1) * 0x510 + ((arg6 >> 3) & 1) * 0x288, arg2, local0, local1);
}
