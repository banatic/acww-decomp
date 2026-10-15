/* func_02017224 @ 0x02017224, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019de4(int);
extern int func_02017f1c(int, int, int, int, int);
extern void func_02019af0(int, int);

void func_02017224(int a, int b)
{
    int t;

    t = func_02019de4(a);
    if (func_02017f1c(a, b, t + 0x22, 6, 0)) {
        func_02019af0(a, 1);
    }
}
