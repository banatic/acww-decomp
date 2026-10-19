/* func_0205ca30 @ 0x0205ca30, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ea1bc(int size, void *heap);
extern int data_021c9b18;

int func_0205ca30(int size, int heapword)
{
    int result;
    result = (int) func_020ea1bc(size, (void *) heapword);
    data_021c9b18 = result;
    return result;
}
