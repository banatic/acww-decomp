/* func_0205395c @ 0x0205395c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e4(void *);
extern unsigned char *func_0206e7bc(void *, int);
extern unsigned char data_021c8c48;

int func_0205395c(int param)
{
    int r4;
    unsigned char *p;

    r4 = param;
    if (r4 >= 1769) {
        r4 = 1768;
    }

    p = func_0206e7bc(func_0206e6e4(&data_021c8c48), r4);
    if (p) {
        return p[0x1a];
    } else {
        return 0;
    }
}
