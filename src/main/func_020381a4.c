/* func_020381a4 @ 0x020381a4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020381a4 {
    unsigned char pad_00[0xbc];
    unsigned int unk_BC;
    unsigned int unk_C0;
    unsigned int unk_C4;
    unsigned char unk_C8;
    unsigned char pad_C9[0x17];
    unsigned int unk_E0;
    unsigned int unk_E4;
};

void func_020381a4(struct UnkStruct_020381a4 *ptr)
{
    ptr->unk_BC = 4;
    ptr->unk_C0 = 0x12c;
    ptr->unk_C4 = 0;
    ptr->unk_C8 = 1;
    ptr->unk_E0 = 0;
    ptr->unk_E4 = 15;
}
