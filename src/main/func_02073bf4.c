/* func_02073bf4 @ 0x02073bf4, 0xe bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073bf4(int *r0, int r1, int r2);

int func_02073bf4(int *r0, int r1, int r2)
{
    int r3;
    int r0_out;

    r3 = r0[9]; // offset 0x24 = 36 = 9 * 4
    r0_out = r2 + (r1 * 3);
    r0_out = r0_out << 12;
    return r3 + r0_out;
}
