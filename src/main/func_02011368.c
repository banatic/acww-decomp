/* func_02011368 @ 0x02011368, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02096284(int x);
extern int func_0209847c(void);

int func_02011368(void *arg)
{
    int res = func_02096284(*(unsigned int *) ((char *) arg + 0x800));
    if (res < 7) {
        return func_0209847c();
    }
    return 0;
}
