/* func_02053d60 @ 0x02053d60, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206e6e4(int);
extern int func_0206e7bc(int, int);

extern unsigned char data_021c8c48[];

int func_02053d60(int arg0)
{
    int val;
    int val2;
    int val3;

    val = arg0;
    if (arg0 < 0x6e9) {
        val2 = arg0;
    } else {
        val2 = 0x6e8;
    }
    val3 = func_0206e6e4((unsigned int) data_021c8c48);
    val = func_0206e7bc(val3, val2);
    if (val != 0) {
        return *(unsigned char *) (val + 0x1d);
    }
    return 0;
}
