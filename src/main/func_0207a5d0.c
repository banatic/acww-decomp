/* func_0207a5d0 @ 0x0207a5d0, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020951bc(unsigned char *);
extern unsigned char *func_0207cec0(unsigned char *, int);
extern int func_0208150c(unsigned char *);
extern int func_02003704(int);
extern int func_020807a8(unsigned char *, unsigned char *);

int func_0207a5d0(unsigned char *a, unsigned char *b)
{
    unsigned char *p;
    int i;

    if (func_020951bc(b) != 0) {
        p = func_0207cec0(a, 0);
        for (i = 0; i < 8; i++) {
            if (func_02003704(func_0208150c(p)) != 0) {
                if (func_020807a8(p, b) == 0) {
                    return 0;
                }
            }
            p += 0x7ec;
        }
        return 1;
    }
    return 0;
}
