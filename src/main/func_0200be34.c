/* func_0200be34 @ 0x0200be34, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(int);
extern int func_0200c3b0(int, int, int, int);

int func_0200be34(int object)
{
    int result = func_02056f94(object + 0x2d0);
    if (result != 0) {
        result = func_0200c3b0(object, 5, 5, -1);
    }
    return result;
}
