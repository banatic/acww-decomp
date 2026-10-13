/* func_020043c4 @ 0x020043c4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int *data_021c67a4;   // placeholder for 0x021c67a4
extern int data_021c67b8[3]; // placeholder for 0x021c67b8
extern void func_020f52a0(int a, int b, int *vec);

void func_020043c4(int a, int b, int *p)
{
    int diff[3];
    if (p == 0) {
        return;
    }
    if (data_021c67a4 == 0) {
        return;
    }
    diff[0] = p[0] - data_021c67b8[0];
    diff[1] = p[1] - data_021c67b8[1];
    diff[2] = p[2] - data_021c67b8[2];
    func_020f52a0(a, b, diff);
}
