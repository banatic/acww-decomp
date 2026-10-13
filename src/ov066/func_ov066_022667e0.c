/* func_ov066_022667e0 @ 0x022667e0, 0x20 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x38];
    int unk_38;
} UnkStruct_022667e0;

extern UnkStruct_022667e0 *data_ov066_0226bdec;

int func_ov066_022667e0(int value)
{
    if (data_ov066_0226bdec != 0) {
        data_ov066_0226bdec->unk_38 = value;
        return 1;
    } else {
        return 0;
    }
}
