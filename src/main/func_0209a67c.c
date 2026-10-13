/* func_0209a67c @ 0x0209a67c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a6ec(void);
extern int func_020951bc(void);

int func_0209a67c(void)
{
    int result;

    if (func_0209a6ec() != 0 && func_020951bc() != 0) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}
