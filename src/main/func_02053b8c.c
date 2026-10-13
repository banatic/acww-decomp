/* func_02053b8c @ 0x02053b8c, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *);
extern void *func_0206e7bc(void *, int);

extern unsigned char data_021c8c48[];

int func_02053b8c(int param)
{
    int r4;
    void *result;
    r4 = param;
    if (param >= 0x6e9) {
        r4 = 0x6e8;
    }
    result = func_0206e7bc(func_0206e6ec((void *) data_021c8c48), r4);
    if (result != 0) {
        return ((unsigned char *) result)[3];
    } else {
        return 0;
    }
}
