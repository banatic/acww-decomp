/* func_02078ab0 @ 0x02078ab0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02078d1c(int *p, int value);
extern int func_02064af4(int a, int b, int c);
extern int data_021d12dc;

void func_02078ab0(int *a, int b)
{
    int result;
    result = func_02078d1c(&data_021d12dc, *a);
    func_02064af4(b, result, 0x2f88);
}
