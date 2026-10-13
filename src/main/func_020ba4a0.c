/* func_020ba4a0 @ 0x020ba4a0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x24];
    unsigned int unk_24;
    unsigned int unk_28;
    unsigned char pad_2C[0x38];
    unsigned int unk_64;
    unsigned char pad_68[0x04];
    unsigned int unk_6C;
} UnkStruct_020ba4a0;

extern UnkStruct_020ba4a0 data_021f8ab0;

unsigned int func_020ba4a0(void)
{
    if (data_021f8ab0.unk_28 != data_021f8ab0.unk_24) {
        return data_021f8ab0.unk_6C;
    } else {
        return data_021f8ab0.unk_64;
    }
}
