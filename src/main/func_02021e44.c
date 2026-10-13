/* func_02021e44 @ 0x02021e44, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081d20(int);
extern int func_02021e68(int);

int func_02021e44(int unused, int x)
{
    if (func_02081d20(x) > 0 && func_02021e68(x) > 0) {
        return 1;
    }
    return 0;
}
