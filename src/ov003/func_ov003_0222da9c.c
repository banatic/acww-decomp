/* func_ov003_0222da9c @ 0x0222da9c, 0xa4 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_ov003_022617bc[];
extern int func_ov003_0222db40(void *a, int c, int m, void *b);
extern int func_ov003_0222d6fc(signed char *c);
extern int func_02061550(unsigned char c);

int func_ov003_0222da9c(void *a, void *b, signed char c, int d)
{
    unsigned char *p;
    int r;
    unsigned char i;

    r = 0;
    p = data_ov003_022617bc;
    for (i = 0; i < 8; i++) {
        if (p[0x248] == 0) {
            if (c == 0x33) {
                r = func_ov003_0222db40(a, c, (unsigned char) d, b);
            } else if (func_ov003_0222d6fc(&c) != 0) {
                r = func_ov003_0222db40(a, c, func_02061550((unsigned char) c), b);
            }
            if (r == 0 && c != 0x33) {
                p[0x248] = 1;
                *(signed char *) (p + 0x24d) = -10;
            }
            return r;
        }
        p += 0x25c;
    }
    return 0;
}
