/* func_02053624 @ 0x02053624, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206e6e8(void *ptr);
extern unsigned char *func_0206e7bc(int a, int b);

extern unsigned char data_021c8c48[];

unsigned char func_02053624(int param)
{
    unsigned char *ptr;

    if (param >= 0x6e9) {
        param = 0x6e8;
    }

    ptr = func_0206e7bc(func_0206e6e8((void *) data_021c8c48), param);
    if (ptr) {
        return *ptr;
    }
    return 0;
}
