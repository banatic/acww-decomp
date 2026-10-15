/* func_0204bb2c @ 0x0204bb2c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bb54(int);
extern int func_0204b42c(int);

int func_0204bb2c(int arg0)
{
    int val;
    int val2;

    if (func_0204bb54(arg0) != 0) {
        val = func_0204b42c(arg0);
        val2 = val - 0xb001;
        return val2;
    }
    return -1;
}
