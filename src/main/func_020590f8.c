/* func_020590f8 @ 0x020590f8, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e895c(void *, int, int);
extern void func_02059674(void *, int);

struct UnkStruct_020590f8 {
    char pad_00[0x60];
    char unk_60[4];
    char unk_64[4];
    char unk_68[4];
    int unk_6C;
    int unk_70;
    int unk_74;
    char pad_78[0x18];
    int unk_90;
    int unk_94;
    int unk_98;
    char pad_9C[0x3a];
    unsigned short unk_D6;
};

void func_020590f8(struct UnkStruct_020590f8 *self)
{
    if ((int) self->unk_D6 >= 2) {
        return;
    }

    func_020e895c(&self->unk_60, self->unk_6C, self->unk_90);
    func_020e895c(&self->unk_64, self->unk_70, self->unk_94);
    func_020e895c(&self->unk_68, self->unk_74, self->unk_98);

    self->unk_D6 += 1;

    if ((int) self->unk_D6 >= 2) {
        func_02059674(self, 0);
    }
}
