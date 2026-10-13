/* func_02087800 @ 0x02087800, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02087500(int param1, int param2);
extern void func_0209e474(int *param1);
extern void func_02087358(int param1, int *param2);
extern void func_02087274(int param1, int *param2);

void func_02087800(int param1)
{
    int local[2];

    func_02087500(param1, 0);
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    func_02087358(param1, local);
    func_02087274(param1, local);
}
