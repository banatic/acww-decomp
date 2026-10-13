/* func_02053be0 @ 0x02053be0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *);
extern void *func_0206e7bc(void *, int);

extern unsigned char data_021c8c48[];

unsigned char func_02053be0(int arg)
{
    int n;
    void *p;
    void *q;

    n = arg;
    if (n >= 0x6e9) {
        n = 0x6e8;
    }
    p = func_0206e6ec(data_021c8c48);
    q = func_0206e7bc(p, n);
    if (q) {
        return ((unsigned char *) q)[5];
    } else {
        return 0;
    }
}
