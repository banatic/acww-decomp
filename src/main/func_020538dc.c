/* func_020538dc @ 0x020538dc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e8(const void *p);
extern unsigned char *func_0206e7bc(void *p, int q);
extern unsigned char data_021c8c48[];

int func_020538dc(int param0)
{
    int r4;
    void *a;
    unsigned char *p;
    unsigned char b;
    int flag;

    r4 = param0;
    if (param0 >= 0x6e9) {
        r4 = 0x6e8;
    }
    a = func_0206e6e8(data_021c8c48);
    p = func_0206e7bc(a, r4);
    if (p != 0) {
        b = p[1];
        flag = (b >> 2) & 1;
        if (flag != 0) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
