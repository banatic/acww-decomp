/* func_02021dcc @ 0x02021dcc, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02081d20(const void *p);
extern int func_02021e68(const void *p);

int func_02021dcc(int unused, const void *arg)
{
    if (func_02081d20(arg) <= 0 && func_02021e68(arg) > 0) {
        return 1;
    }
    return 0;
}
