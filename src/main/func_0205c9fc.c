/* func_0205c9fc @ 0x0205c9fc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020ea1bc(int size, void *heap);
extern int data_021c9b14;

int func_0205c9fc(int size, int heapword)
{
    int result;
    result = (int) func_020ea1bc(size, (void *) heapword);
    data_021c9b14 = result;
    return result;
}
