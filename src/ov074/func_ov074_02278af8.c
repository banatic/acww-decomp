/* func_ov074_02278af8 @ 0x02278af8, 0x24 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203cfc0(int *out, int a, int b);
extern int func_020e9948(int a, int b);
extern void func_ov074_02278a90(int *out, int b);

void func_ov074_02278af8(int *out, int param1, int param2)
{
    int temp;
    temp = func_0203cfc0(out, param1, param2);
    *out = func_020e9948(param1, temp);
    func_ov074_02278a90(out, param2);
}
