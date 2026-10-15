/* func_0205cf4c @ 0x0205cf4c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c9b44;
extern int data_020dd6ac;
extern int func_02064328(int *obj, int *tbl, unsigned int hi, unsigned int raw);

int *func_0205cf4c(unsigned int raw)
{
    func_02064328(&data_021c9b44, &data_020dd6ac, raw >> 5, raw);
    return &data_021c9b44;
}
