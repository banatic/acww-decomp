/* func_020c3610 @ 0x020c3610, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(int);
extern int func_0203e020(int);
extern int func_020c3690(int, int);

int func_020c3610(int arg0)
{
    int r4;
    int result;

    r4 = arg0;
    if (func_02014868(r4 + 0x618) == 0) {
        func_0203e020(r4);
        func_020c3690(r4, 2);
    }
    return 1;
}
