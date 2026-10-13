/* func_02097d18 @ 0x02097d18, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02097d18(unsigned char *param0, int param1);

void func_02097d18(unsigned char *param0, int param1)
{
    unsigned char *r5;
    int r4;
    unsigned char r3;
    int r2;
    int r0;

    r5 = param0 + 4;
    r4 = param1 >> 3;
    r3 = r5[r4];
    r2 = 1;
    r0 = 7;
    r2 = r2 << (param1 & r0);
    r3 = r3 | r2;
    r5[r4] = r3;
}
