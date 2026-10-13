/* func_020c234c @ 0x020c234c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *);
extern int func_0203e020(void *);
extern int func_020c26b4(void *, int);

int func_020c234c(void *arg0)
{
    void *r4;
    int result;

    r4 = arg0;
    result = func_02014868((char *) r4 + 0x618);
    if (result == 0) {
        func_0203e020(r4);
        func_020c26b4(r4, 7);
    }
    return 1;
}
