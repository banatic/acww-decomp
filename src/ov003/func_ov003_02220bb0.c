/* func_ov003_02220bb0 @ 0x02220bb0, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223cfe4;
extern void func_ov003_022213f8(int *addr, int p0, int *p2, int *p3, int a, int b, int c, int d);

void func_ov003_02220bb0(int p0, int p1, int *p2, int *p3)
{
    int local3[3];
    int local2[2];
    local3[0] = p3[0];
    local3[1] = p3[1];
    local3[2] = p3[2];
    local2[0] = p2[0];
    local2[1] = p2[1];
    func_ov003_022213f8(&data_ov003_0223cfe4, p0, local2, local3, 13, p1, 0, 0);
}
