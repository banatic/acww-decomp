/* func_0205c8c4 @ 0x0205c8c4, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c9afc; // at 0x021c9afc
extern void *GX_ResetBankForSubOBJExtPltt(int size, void *heap);

int func_0205c8c4(int size, int type)
{
    int result = (int) GX_ResetBankForSubOBJExtPltt(size, (void *) type);
    data_021c9afc = result;
    return result;
}
