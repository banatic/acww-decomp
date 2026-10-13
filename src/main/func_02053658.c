/* func_02053658 @ 0x02053658, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0206e6e4(void *ptr);
extern void *func_0206e7bc(void *ptr, int index);
extern char data_021c8c48;

signed char func_02053658(int param)
{
    int index;
    void *base;
    void *ptr;

    if (param < 0x6e9) {
        index = param;
    } else {
        index = 0x6e8;
    }

    base = func_0206e6e4(&data_021c8c48);
    ptr = func_0206e7bc(base, index);

    return (signed char) (ptr ? ((unsigned char *) ptr)[0x1c] : 0);
}
