/* func_020584c4 @ 0x020584c4, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020e895c(void *out, int a, int b);
struct UnkStruct_020584c4;
extern void func_02059674(struct UnkStruct_020584c4 *self, int arg);

struct UnkStruct_020584c4 {
    unsigned char pad_00[0x60];
    int unk_60;
    int unk_64;
    int unk_68;
    int unk_6C;
    int unk_70;
    int unk_74;
    unsigned char pad_78[0x90 - 0x78];
    int unk_90;
    int unk_94;
    int unk_98;
    unsigned char pad_9C[0xd6 - 0x9c];
    unsigned short state;
};

void func_020584c4(struct UnkStruct_020584c4 *this)
{
    if ((int) this->state >= 4) {
        return;
    }
    func_020e895c(&this->unk_60, this->unk_6C, this->unk_90);
    func_020e895c(&this->unk_64, this->unk_70, this->unk_94);
    func_020e895c(&this->unk_68, this->unk_74, this->unk_98);
    this->state++;
    if ((int) this->state < 4) {
        return;
    }
    func_02059674(this, 0);
}
