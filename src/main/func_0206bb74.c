/* func_0206bb74 @ 0x0206bb74, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206bef8(void *arg);

int func_0206bb74(void *p)
{
    if (func_0206bef8((char *) p + 0x60) && func_0206bef8((char *) p + 0x9c)) {
        return 1;
    }
    return 0;
}
