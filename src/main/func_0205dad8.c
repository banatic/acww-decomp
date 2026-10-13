/* func_0205dad8 @ 0x0205dad8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c9d68;
extern int data_020dd6f0;
extern void func_02064328(int *obj, int *tbl, unsigned int hi, unsigned int raw);

int *func_0205dad8(unsigned int raw)
{
    func_02064328(&data_021c9d68, &data_020dd6f0, raw >> 5, raw);
    return &data_021c9d68;
}
