/* func_02036a30 @ 0x02036a30, 0x2a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02036648(void);
extern int func_0203734c(int x);

int func_02036a30(unsigned char *p)
{
    unsigned char *q = p + 0x13;
    int v = func_0203734c(func_02036648());
    int b = (p[0x13] | v) ? 1 : 0;
    *q = b;
    return b;
}
