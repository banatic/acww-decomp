/* func_02053c34 @ 0x02053c34, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *p);
extern void *func_0206e7bc(void *p, int n);
extern int data_021c8c48;

unsigned char func_02053c34(int param)
{
    void *p;
    void *res;

    if (param >= 0x6e9) {
        param = 0x6e8;
    }
    p = func_0206e6ec(&data_021c8c48);
    res = func_0206e7bc(p, param);
    if (res) {
        return ((unsigned char *) res)[4];
    } else {
        return 0;
    }
}
