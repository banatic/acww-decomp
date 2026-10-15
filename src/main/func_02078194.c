/* func_02078194 @ 0x02078194, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020e1858;
extern void func_020781bc(void *object);
extern void *func_02077f14(int index, int value);

void func_02078194(void *object)
{
    func_020781bc(object);
    func_02077f14(0, data_020e1858);
    func_02077f14(1, data_020e1858);
}
