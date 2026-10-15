/* func_0205ca98 @ 0x0205ca98, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *GX_ResetBankForSubOBJExtPltt(int size, void *heap);
extern int data_021c9b20;

int func_0205ca98(int size, int heapword)
{
    int result;
    result = (int) GX_ResetBankForSubOBJExtPltt(size, (void *) heapword);
    data_021c9b20 = result;
    return result;
}
