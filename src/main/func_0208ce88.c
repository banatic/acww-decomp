/* func_0208ce88 @ 0x0208ce88, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203ec98(void);
extern int func_02070070(void);
extern int func_0206fd04(void);
extern int func_0206fd10(void);

unsigned char func_0208ce88(unsigned char *self)
{
    unsigned char r6;
    int a, b, c, d;
    int r4, r7;

    r6 = self[0xa8];
    if (r6 != 0) {
        a = func_0203ec98();
        b = func_02070070();
        r4 = 0;
        if (a != 0 && b == 0) {
            r4 = 1;
        }
        r7 = 0;
        if (a != 0 && b != 0) {
            c = func_0206fd04();
            d = func_0206fd10();
            if (c != 0) {
                if (d < 0x1000) {
                    r7 = 1;
                }
            } else {
                r7 = 1;
            }
        }
        if (r4 != 0 || r7 != 0) {
            r6 = 0;
            if (r4 != 0) {
                *(int *) (self + 0xc8) = 0;
            }
        }
    } else {
        *(int *) (self + 0xc8) = 0;
    }
    return r6;
}
