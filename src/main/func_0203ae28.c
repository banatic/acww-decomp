/* func_0203ae28 @ 0x0203ae28, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb8];
    int unk_B8;
    int unk_BC;
    unsigned char pad_C0[8];
    int unk_C8;
    unsigned char pad_CC[0x100];
    int unk_1CC;
    int unk_1D0;
    int unk_1D4;
    unsigned char pad_1D8[0x1f6 - 0x1d8];
    unsigned char unk_1F6;
    unsigned char pad_1F7;
    int unk_1F8;
} UnkStruct_0203ae28;
extern UnkStruct_0203ae28 *data_021c67a4;
int func_0203ae28(int *v)
{
    int *d;
    if (data_021c67a4->unk_1F8 == 0x13) {
        data_021c67a4->unk_C8 = 0;
        data_021c67a4->unk_B8 = 0;
        data_021c67a4->unk_BC = 0x15000;
        return 1;
    }
    d = &data_021c67a4->unk_1CC;
    d[0] = v[0];
    d[1] = v[1];
    d[2] = v[2];
    data_021c67a4->unk_C8 = 0;
    data_021c67a4->unk_1F6 = 3;
    return 1;
}
