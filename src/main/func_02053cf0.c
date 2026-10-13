/* func_02053cf0 @ 0x02053cf0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206e6ec(int);
extern int func_0206e7bc(int, int);

extern unsigned char data_021c8c48[];

int func_02053cf0(int r0)
{
    int r4;
    int r1;
    int r0_2;

    r4 = r0;
    if (r4 < 0x6e9) {
    } else {
        r4 = 0x6e8;
    }
    r0_2 = func_0206e6ec((unsigned int) data_021c8c48);
    r1 = r4;
    r0_2 = func_0206e7bc(r0_2, r1);
    if (r0_2 != 0) {
        return *(unsigned char *) (r0_2 + 1);
    } else {
        return 0;
    }
}
