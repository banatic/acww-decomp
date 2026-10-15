/* func_0205c994 @ 0x0205c994, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *GX_ResetBankForSubOBJExtPltt(int size, void *heap);
extern unsigned int data_021c9b0c;

int func_0205c994(int size, int heapword)
{
    int result;
    result = (int) GX_ResetBankForSubOBJExtPltt(size, (void *) heapword);
    data_021c9b0c = result;
    return result;
}
