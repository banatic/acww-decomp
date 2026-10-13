/* func_02090858 @ 0x02090858, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02090858 {
    char data[0x530];
};
extern int GX_ResetBankForSubOBJExtPltt(int, int);
extern void func_02090788(struct UnkStruct_02090858 *, int);
extern int data_021d52c8;
extern int data_021fbe94;

void func_02090858(struct UnkStruct_02090858 *arr)
{
    int i;
    if (data_021d52c8 == 0) {
        data_021d52c8 = GX_ResetBankForSubOBJExtPltt(0x2800, data_021fbe94);
    }
    for (i = 0; i < 4; i++) {
        func_02090788(arr + i, i);
    }
}
