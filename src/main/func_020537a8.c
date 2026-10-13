/* func_020537a8 @ 0x020537a8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e8(void *);
extern void *func_0206e7bc(void *, int);

extern unsigned char data_021c8c48[];

int func_020537a8(int param)
{
    int x;
    void *p;
    void *q;
    x = param;
    if (x >= 0x6E9) {
        x = 0x6E8;
    }
    p = func_0206e6e8((void *) data_021c8c48);
    q = func_0206e7bc(p, x);
    if (q != 0) {
        if ((((unsigned char *) q)[1] >> 6) & 1) {
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
