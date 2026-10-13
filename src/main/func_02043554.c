/* func_02043554 @ 0x02043554, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02044858(int, int);
extern int func_020435fc(int, int);

int func_02043554(int a, int b)
{
    int c = b;
    return func_020435fc(func_02044858(a, b), c);
}
