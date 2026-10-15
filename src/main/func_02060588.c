/* func_02060588 @ 0x02060588, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020606fc(int, int);
extern int func_021077e8(int);
extern int func_020606f0(int, int);
extern void func_02055b50(int, int);

void func_02060588(int a, int b)
{
    int temp;
    temp = func_021077e8(func_020606fc(a, b));
    func_02055b50(func_020606f0(a, b), temp);
}
