/* func_0205f974 @ 0x0205f974, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cacfc;
extern int data_020dd7b0;
extern void func_02064328(int *obj, int *tbl, unsigned int hi, unsigned int raw);

int *func_0205f974(unsigned int raw)
{
    func_02064328(&data_021cacfc, &data_020dd7b0, raw >> 5, raw);
    return &data_021cacfc;
}
