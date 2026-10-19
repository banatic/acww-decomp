/* func_0205c960 @ 0x0205c960, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ea1bc(int size, void *heap);
extern int data_021c9b08;

int func_0205c960(int size, int heapword)
{
    int result;
    result = (int) func_020ea1bc(size, (void *) heapword);
    data_021c9b08 = result;
    return result;
}
