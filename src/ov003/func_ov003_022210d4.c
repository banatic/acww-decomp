/* func_ov003_022210d4 @ 0x022210d4, 0x44 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223cfe4;
extern int func_ov003_022213f8(int *dest, int self, int *arr1, int *arr2, int a, int b, short c, int d);

void func_ov003_022210d4(int self, int arg1, int *p2, int *p3, short arg4, int arg5)
{
    int local2[2];
    int local3[3];

    local3[0] = p3[0];
    local3[1] = p3[1];
    local3[2] = p3[2];
    local2[0] = p2[0];
    local2[1] = p2[1];

    func_ov003_022213f8(&data_ov003_0223cfe4, self, local2, local3, 5, arg1, arg4, arg5);
}
