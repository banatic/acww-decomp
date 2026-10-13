/* func_0205389c @ 0x0205389c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e8(void *);
extern void *func_0206e7bc(void *, int);
extern char data_021c8c48;

int func_0205389c(int arg)
{
    int r4;
    void *p;
    void *q;
    r4 = arg;
    if (r4 >= 0x6e9) {
        r4 = 0x6e8;
    }
    p = func_0206e6e8(&data_021c8c48);
    q = func_0206e7bc(p, r4);
    if (q != 0) {
        if (((((unsigned char *) q)[1] >> 3) & 1) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
