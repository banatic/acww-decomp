/* func_02038d9c @ 0x02038d9c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02011ec8(void);
extern void func_02039380(void *);

int func_02038d9c(void *arg0)
{
    void *r4;
    int r0;

    r4 = arg0;
    r0 = func_02011ec8();
    if (r0 != 0) {
        r4 = (char *) r4 + 0x54;
        func_02039380(r4);
    }
    return 1;
}
