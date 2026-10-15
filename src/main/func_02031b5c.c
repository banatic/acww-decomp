/* func_02031b5c @ 0x02031b5c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_01ffcb2c(int, int);
int func_02031b5c(int argument0, int argument1)
{
    int x;
    x = func_01ffcb2c((int) argument0, (int) argument1);
    if (x == 8) {
        return 1;
    }
    if (x == 7 || (x >= 11 && x <= 18)) {
        return 2;
    }
    return 0;
}
