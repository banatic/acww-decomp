/* func_0201873c @ 0x0201873c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bd4(unsigned char *p);
extern void func_02019af0(unsigned char *p, int n);

int func_0201873c(unsigned char *p)
{
    int t;

    t = func_02057bd4(p);
    if (t) {
        return t;
    }
    func_02019af0(p, 1);
    p[0x98] = 5;
    return 5;
}
