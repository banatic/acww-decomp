/* func_02053cbc @ 0x02053cbc, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *);
extern void *func_0206e7bc(void *, int);

extern unsigned char data_021c8c48[];

int func_02053cbc(int arg)
{
    int r;
    void *p1;
    unsigned char *p2;

    r = arg;
    if (r >= 1769) {
        r = 1768;
    }
    p1 = func_0206e6ec((void *) data_021c8c48);
    p2 = (unsigned char *) func_0206e7bc(p1, r);
    if (p2) {
        return p2[2];
    } else {
        return 0;
    }
}
