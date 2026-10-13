/* func_ov066_02268268 @ 0x02268268, 0x64 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x93];
    unsigned char unk_93;
    unsigned char unk_94;
} UnkStruct_02268268;

extern UnkStruct_02268268 *data_ov066_0226bdf4;
extern unsigned int data_ov066_0226bdf8;

void func_ov066_02268268(void)
{
    data_ov066_0226bdf4->unk_94++;
    if (data_ov066_0226bdf4->unk_94 < 4) {
        return;
    }
    data_ov066_0226bdf4->unk_94 = 0;
    data_ov066_0226bdf8 = data_ov066_0226bdf8 * 0x5eedf715u + 0x1b0cb173u;
    data_ov066_0226bdf4->unk_93 = data_ov066_0226bdf8 & 3;
}
