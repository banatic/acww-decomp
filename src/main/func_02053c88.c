/* func_02053c88 @ 0x02053c88, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6ec(void *arg);
extern void *func_0206e7bc(void *arg1, int arg2);

extern unsigned char data_021c8c48[];

unsigned char func_02053c88(int param)
{
    int idx = param;
    void *entry;

    if (idx >= 0x6e9) {
        idx = 0x6e8;
    }
    entry = func_0206e7bc(func_0206e6ec((void *) data_021c8c48), idx);
    if (entry) {
        return *(unsigned char *) entry;
    }
    return 0;
}
