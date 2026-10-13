/* func_ov110_0229cce8 @ 0x0229cce8, 0x2a bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov110_0229d458(void *a, int b, unsigned short c, unsigned char d);

struct UnkStruct_ec {
    char pad_00[0xec];
    unsigned short unk_EC;
    unsigned short unk_EE;
    unsigned char unk_F0;
    unsigned char unk_F1;
};

int func_ov110_0229cce8(struct UnkStruct_ec *this, int arg1)
{
    if (this->unk_F1 == 1) {
        func_ov110_0229d458(this, arg1, this->unk_EC, this->unk_F0);
    }
    this->unk_F1 = 0;
    return 0;
}
