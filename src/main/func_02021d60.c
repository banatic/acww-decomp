/* func_02021d60 @ 0x02021d60, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081d60(int param);
extern int func_02081398(int param1, int param2);

int func_02021d60(int a, int b)
{
    return func_02081398(a, func_02081d60(b));
}
