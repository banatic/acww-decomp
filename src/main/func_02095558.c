/* func_02095558 @ 0x02095558, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984fc(int param);
extern void func_020997b4(int param1, int param2);

int func_02095558(int a, int b)
{
    int result = func_020984fc(b);
    if (result == 0) {
        return 0;
    }
    func_020997b4(result, a);
    return 1;
}
