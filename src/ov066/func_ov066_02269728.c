/* func_ov066_02269728 @ 0x02269728, 0x20 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02269728 {
    char pad_00[0x88];
    int unk_88;
} UnkStruct_02269728;

extern UnkStruct_02269728 *data_ov066_0226bdf4;
extern void func_ov066_022696b4(int arg1, int arg2);

void func_ov066_02269728(void)
{
    func_ov066_022696b4(data_ov066_0226bdf4->unk_88, 0);
}
