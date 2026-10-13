/* func_02078e98 @ 0x02078e98, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *a, int *b, int c);
extern void func_02078ec0(int a, int b, int c);

void func_02078e98(int arg0, int arg1)
{
    int a = 0;
    int b = 0;
    func_0204f818(&a, &b, arg0);
    func_02078ec0(a, b, arg1);
}
