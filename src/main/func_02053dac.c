/* func_02053dac @ 0x02053dac, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e4(char *);
extern void *func_0206e7bc(void *, int);
extern char data_021c8c48;

int func_02053dac(int a)
{
    int v;
    void *p;
    void *q;
    int byte;

    v = a;
    if (v >= 0x6e9) {
        v = 0x6e8;
    }
    p = func_0206e6e4(&data_021c8c48);
    q = func_0206e7bc(p, v);
    if (q != 0) {
        byte = ((unsigned char *) q)[0x19];
    } else {
        byte = 0;
    }
    return (byte << 12) >> 4;
}
