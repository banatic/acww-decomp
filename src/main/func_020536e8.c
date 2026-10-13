/* func_020536e8 @ 0x020536e8, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021c8c48;
extern void *func_0206e6e8(unsigned char *);
extern unsigned char *func_0206e7bc(void *, int);

int func_020536e8(int param)
{
    unsigned char *q;
    if (param >= 0x6e9) {
        param = 0x6e8;
    }
    q = func_0206e7bc(func_0206e6e8(&data_021c8c48), param);
    if (q != 0) {
        if (q[2] & 1) {
            return 1;
        }
        return 0;
    } else {
        return 0;
    }
}
