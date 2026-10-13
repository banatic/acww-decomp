/* func_020821d4 @ 0x020821d4, 0x56 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char *func_0208222c(int a, int b);
extern int func_0209e3ac(int a, void *b, int c);

int func_020821d4(int a, int b)
{
    unsigned int buf[3];
    unsigned char *p;

    p = func_0208222c(a, b);
    buf[0] = 0;
    buf[1] = 0;
    ((unsigned char *) buf)[2] = p[0];
    ((unsigned char *) buf)[1] = p[1];
    if (func_0209e3ac(b, buf, 6) == 1) {
        ((unsigned char *) buf)[2] = p[2];
        ((unsigned char *) buf)[1] = p[3];
        return func_0209e3ac(b, buf, 6) == -1;
    }
    return 0;
}
