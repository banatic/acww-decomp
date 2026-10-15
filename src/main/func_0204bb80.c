/* func_0204bb80 @ 0x0204bb80, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bba8(int);
extern int func_0204b42c(int);

int func_0204bb80(int arg0)
{
    int val;
    int val2;

    if (func_0204bba8(arg0) != 0) {
        val = func_0204b42c(arg0);
        val2 = val - 0x500d;
    } else {
        val2 = -1;
    }
    return val2;
}
