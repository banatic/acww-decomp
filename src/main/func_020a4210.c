/* func_020a4210 @ 0x020a4210, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a0284(int a, int b);
extern int func_020b1130(int a);

int func_020a4210(int a)
{
    return func_020b1130(func_020a0284(a, 1));
}
