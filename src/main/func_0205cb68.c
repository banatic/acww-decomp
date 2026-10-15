/* func_0205cb68 @ 0x0205cb68, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *GX_ResetBankForSubOBJExtPltt(int size, void *heap);
extern int data_021c9b30;

void func_0205cb68(int size, void *heap)
{
    data_021c9b30 = (int) GX_ResetBankForSubOBJExtPltt(size, heap);
}
