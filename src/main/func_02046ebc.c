/* func_02046ebc @ 0x02046ebc, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern int func_0204e414(int);
extern int func_02048cb8(int, int, int, int, int, int, int);
extern int func_02048e34(void);

int func_02046ebc(int param)
{
    int r5 = func_020644cc(4);
    int local = func_0204e414(r5);
    int r4 = 0;
    int r6 = r4;
    while (r4 < 4) {
        if (func_02048cb8(param, local, r5 + 1, 4, 0x1520, (int) func_02048e34, r6) != 0) {
            return 1;
        }
        r5 = (r5 + 1) & 3;
        r4++;
    }
    return 0;
}
