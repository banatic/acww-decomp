/* func_02053b2c @ 0x02053b2c, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *);
extern unsigned char *func_0206e7bc(void *, int);

extern unsigned char data_021c8c48[];

int func_02053b2c(int arg)
{
    int x = arg;
    unsigned char *res;
    if (x >= 1769) {
        x = 1768;
    }
    res = func_0206e7bc(func_0206e6ec((void *) data_021c8c48), x);
    if (res != 0) {
        if (((res[7] >> 4) & 1) != 0) {
            return 1;
        }
        return 0;
    }
    return 0;
}
