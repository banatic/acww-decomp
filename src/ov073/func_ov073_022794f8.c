/* func_ov073_022794f8 @ 0x022794f8, 0x38 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c67a4;
extern int data_021c67d0[3];
extern int func_ov073_02279530(int a, int *b, int c);

int func_ov073_022794f8(int a)
{
    int p = a + 0x5c;
    int r = 0;
    if (data_021c67a4) {
        int local[3];
        local[0] = data_021c67d0[0];
        local[1] = data_021c67d0[1];
        local[2] = data_021c67d0[2];
        r = func_ov073_02279530(a, local, p);
    }
    return r;
}
