/* func_0207388c @ 0x0207388c, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020738ac(int, int, int);

void func_0207388c(int arg0)
{
    int r4;
    int r5;
    int r6;

    r5 = arg0;
    r4 = 0x45;
    r6 = 0;
    do {
        func_020738ac(r5, r4, r6);
        r4 = r4 - 1;
    } while (r4 >= 0);
}
