/* func_0205dd60 @ 0x0205dd60, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c9e34;
extern int data_020dd704;
extern int func_02064328(int *obj, int *tbl, unsigned int hi, unsigned int raw);

int *func_0205dd60(unsigned int raw)
{
    func_02064328(&data_021c9e34, &data_020dd704, raw >> 5, raw);
    return &data_021c9e34;
}
