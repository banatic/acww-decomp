/* func_ov066_02267db4 @ 0x02267db4, 0x4c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

extern int func_ov066_0226a1b0(int);
struct UnkStruct_02267db4 {
    char pad_00[0x10];
    unsigned char *arr;
};
struct UnkStruct_02267db4_2 {
    char pad_00[0x8e];
    unsigned char unk_8E;
};
extern struct UnkStruct_02267db4 *data_ov066_0226bdec;
extern struct UnkStruct_02267db4_2 *data_ov066_0226bdf4;

int func_ov066_02267db4(int index)
{
    if (data_ov066_0226bdec->arr) {
        return data_ov066_0226bdec->arr[index];
    }
    return func_ov066_0226a1b0(data_ov066_0226bdf4->unk_8E);
}
