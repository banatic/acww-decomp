/* func_0204cfa4 @ 0x0204cfa4, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204cfc8(int, int);
extern void func_0205bdb0(void);
extern int data_021fbe94;

int func_0204cfa4(int arg)
{
    if (func_0204cfc8(arg, data_021fbe94) == 0) {
        return 0;
    }
    func_0205bdb0();
    return 1;
}
