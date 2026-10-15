/* func_02095ed0 @ 0x02095ed0, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02095e84(int, int);
extern int func_02095ea4(int, int);

int func_02095ed0(int param, int argument1)
{
    if (param != 0) {
        return func_02095ea4(0x10, argument1);
    } else {
        return func_02095e84(0x10, (int) argument1);
    }
}
