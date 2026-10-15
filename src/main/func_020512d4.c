/* func_020512d4 @ 0x020512d4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020512d4 {
    char pad_00[0x28];
    int unk_28;
    char pad_2C[0x8];
    int unk_34;
    char pad_38[0x1f];
    unsigned char unk_57;
    char pad_58[0xc];
    int unk_64;
    int unk_68;
    char pad_6C[0x9];
    unsigned char unk_75;
    char pad_76[0x2];
    int unk_78;
} UnkStruct_020512d4;

extern int func_020516b8(int table, int key);
extern int func_020510c8(UnkStruct_020512d4 *this);
extern void func_02051034(UnkStruct_020512d4 *this);
extern void func_02050fc8(UnkStruct_020512d4 *this, int old);

void func_020512d4(UnkStruct_020512d4 *this, int key)
{
    int old_68;
    this->unk_64 = func_020516b8(this->unk_28, key);
    if (this->unk_64 == -1) {
        this->unk_64 = func_020516b8(this->unk_28, 0x0000ff20);
    }
    old_68 = this->unk_68;
    this->unk_68 = this->unk_68 + func_020510c8(this);
    func_02051034(this);
    this->unk_68 = this->unk_68 + this->unk_34;
    if (this->unk_75 != 0 && this->unk_57 != 0) {
        func_02050fc8(this, old_68);
    }
    this->unk_78++;
}
