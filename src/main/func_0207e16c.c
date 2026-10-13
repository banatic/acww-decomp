/* func_0207e16c @ 0x0207e16c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Triple {
    int a;
    int b;
    int c;
};

extern void func_0209e474(void *p);

int func_0207e16c(void)
{
    struct Triple s;
    s.a = 0;
    s.b = 0;
    func_0209e474(&s);
    if (*(unsigned char *) &s.b == 12 || (*(unsigned char *) &s.b >= 1 && *(unsigned char *) &s.b <= 2)) {
        return 1;
    }
    return 0;
}
