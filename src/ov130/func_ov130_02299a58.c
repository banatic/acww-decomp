/* func_ov130_02299a58 @ 0x02299a58, 0x68 bytes, Thumb, module ov130
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov130_02299a08(int a, int b, int c, int d);

void func_ov130_02299a58(int a, int b, int c, int d, int e)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < e) {
        if (b == 0) {
            if (i == 0) {
                func_ov130_02299a08(a, j, c, d);
            } else {
                func_ov130_02299a08(a, 0xb, c, d);
            }
        } else {
            func_ov130_02299a08(a, b % 10, c, d);
            b = b / 10;
        }
        c--;
        i++;
    }
}
