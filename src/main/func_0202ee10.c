/* func_0202ee10 @ 0x0202ee10, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082f04(int);
extern int func_02078a1c(int);
extern int func_02055478(int, int);
extern int func_02054354(int, int);

int func_0202ee10(int arg0)
{
    int local_0;
    int val;
    int val2;

    val = func_02082f04(arg0 + 0x640);
    val2 = func_02078a1c(val);
    if (func_02055478(arg0 + 0xec, val2) == 0) {
        return 0;
    }
    val2 = func_02078a1c(val);
    if (func_02054354(arg0 + 0xec, val2) != 0) {
        return 1;
    }
    return 0;
}
