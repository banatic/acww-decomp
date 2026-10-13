/* func_02053de4 @ 0x02053de4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e4(int arg);
extern void *func_0206e7bc(void *arg, int arg2);

extern unsigned char data_021c8c48[];

unsigned char func_02053de4(int val)
{
    void *res;

    if (val >= 0x6e9) {
        val = 0x6e8;
    }
    res = func_0206e7bc(func_0206e6e4((unsigned int) data_021c8c48), val);
    if (res) {
        return ((unsigned char *) res)[0x18];
    }
    return 0;
}
