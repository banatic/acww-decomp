/* func_0205c7b4 @ 0x0205c7b4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203cfc0(int);
extern int func_020b65c4(int);
extern int func_020b5df8(int);
extern int func_02085f08(int);
extern int func_020ea0e0(int, int);
extern int data_021c9af4;

void func_0205c7b4(int param)
{
    int size = 0;
    int result = 0;
    int d, extra;

    size += (func_0203cfc0(param) + 3) & ~3;
    d = func_020b5df8(func_020b65c4(3));
    extra = func_02085f08(d);
    result += size * (d + extra + 1);
    data_021c9af4 = func_020ea0e0(result, param);
}
