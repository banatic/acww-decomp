/* func_ov003_02221118 @ 0x02221118, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223cfe4;
extern void func_ov003_022213f8(int *a0, int a1, int *a2, int *a3, int a4, int a5, int a6, int a7);

void func_ov003_02221118(int a, int b, int *p)
{
    int pair[2];
    int triple[3];
    triple[0] = 0;
    triple[1] = 0;
    triple[2] = 0;
    pair[0] = p[0];
    pair[1] = p[1];
    func_ov003_022213f8(&data_ov003_0223cfe4, a, pair, triple, 4, b, 0, 0);
}
