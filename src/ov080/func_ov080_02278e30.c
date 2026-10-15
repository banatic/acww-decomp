/* func_ov080_02278e30 @ 0x02278e30, 0x18 bytes, Thumb, module ov080
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(int *a);
extern int data_ov080_0227925c;

int *func_ov080_02278e30(int *p)
{
    *p = (int) &data_ov080_0227925c;
    func_0202eb20(p);
    return p;
}
