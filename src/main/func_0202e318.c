/* func_0202e318 @ 0x0202e318, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02082f78(int);
extern int func_02078a5c(int);
extern int func_02055478(int, int);
extern int func_02054354(int, int);

int func_0202e318(int a)
{
    int X;
    int Y;
    int Z;
    X = func_02082f78(a + 0x828);
    Y = func_02078a5c(X);
    if (func_02055478(a + 0xec, Y) == 0) {
        return 0;
    }
    Z = func_02078a5c(X);
    if (func_02054354(a + 0xec, Z) == 0) {
        return 0;
    }
    return 1;
}
