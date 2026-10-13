/* func_0204bc28 @ 0x0204bc28, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(short *a, int b);
extern int func_0204bc64(short *a);
extern short func_0204bc50(int a, int b);

void func_0204bc28(short *dest, int arg1)
{
    if (func_0204bcdc(dest, arg1) != 0) {
        *dest = func_0204bc50(func_0204bc64(dest), arg1);
    }
}
