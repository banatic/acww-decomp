/* func_020550e4 @ 0x020550e4, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8];
    unsigned int unk_08;
    unsigned char pad_0C[0x30];
    unsigned int unk_3C;
    unsigned char pad_40[0x64];
    unsigned int unk_A4;
    unsigned char pad_A8[0xC];
    unsigned int *unk_B4;
} UnkStruct_020550e4;

void func_020550e4(UnkStruct_020550e4 *this, int param1)
{
    this->unk_A4 = param1 << 12;
    *this->unk_B4 = this->unk_A4;
    if (this->unk_3C != 0) {
        this->unk_08 |= 1;
    }
}
