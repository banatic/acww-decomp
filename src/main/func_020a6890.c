/* func_020a6890 @ 0x020a6890, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a72d0(int);
extern int func_020a6878(int);
extern void func_020a7394(int, int, int, int, int);

void func_020a6890(int a, int *out1, int *out2)
{
    int found = 4;
    int i;
    int x;

    for (i = 3; i >= 0; i--) {
        if (func_020a72d0(i)) {
            found = i;
            break;
        }
    }
    if (found < 4) {
        return;
    }
    x = func_020a6878(a);
    if (x >= 4) {
        return;
    }
    func_020a7394(x, 0x3f, 0, 1, 4);
    *out1 = x;
    *out2 = 4;
}
