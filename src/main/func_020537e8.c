/* func_020537e8 @ 0x020537e8, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206e6e4(int ptr);
extern int func_0206e7bc(int a, int b);

extern unsigned char data_021c8c48[];

int func_020537e8(int param)
{
    int a;
    int v;
    a = param;
    if (a >= 1769) {
        a = 1768;
    }
    v = func_0206e7bc(func_0206e6e4((unsigned int) data_021c8c48), a);
    if (v) {
        return v;
    } else {
        return 0;
    }
}
