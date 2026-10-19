/* func_0205cb34 @ 0x0205cb34, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ea1bc(int size, void *heap);
extern int data_021c9b2c;

void func_0205cb34(int size, void *heap)
{
    data_021c9b2c = (int) func_020ea1bc(size, heap);
}
