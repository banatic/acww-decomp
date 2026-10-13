/* func_02073bac @ 0x02073bac, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02077b58(int);

void func_02073bac(int r0, int r1, int r2, int r3)
{
    int r5 = r0;
    int r4 = r2;
    int r6 = r3;
    int r0_2 = r1;
    int result = func_02077b58(r0_2);
    int r1_2 = result * 12;
    int r0_3 = r5 + r1_2;
    int r0_4 = r0_3 + (r4 << 2);
    *(int *) (r0_4 + 0x28) = r6;
}
