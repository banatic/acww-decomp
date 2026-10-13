/* func_02062fe8 @ 0x02062fe8, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204bcdc(void *arg);
extern int func_0206300c(void *arg, int flag);

int func_02062fe8(void *arg)
{
    if (func_0204bcdc(arg) != 0 && func_0206300c(arg, 0) == 4) {
        return 1;
    }
    return 0;
}
