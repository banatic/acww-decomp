/* func_02046d14 @ 0x02046d14, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204df30(int i);
extern void func_02046df4(int a, int b);

void func_02046d14(int param)
{
    int i;
    for (i = 0; i < 5; i++) {
        func_02046df4(param, func_0204df30(i));
    }
}
