/* func_0205c92c @ 0x0205c92c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *GX_ResetBankForSubOBJExtPltt(int size, void *heap);
extern int data_021c9b04;

int func_0205c92c(int size, int heapword)
{
    int result;
    result = (int) GX_ResetBankForSubOBJExtPltt(size, (void *) heapword);
    data_021c9b04 = result;
    return result;
}
