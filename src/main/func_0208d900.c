/* func_0208d900 @ 0x0208d900, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0208d900 {
    char pad_00[0x28];
    int unk_28;
    int unk_2C;
    char pad1[0x8];
    unsigned char unk_38;
    unsigned char unk_39;
    char pad2[0x16];
    int unk_50;
    char pad_54;
    unsigned char unk_55;
};

struct UnkStruct_0208d900_2 {
    char pad_00[0x38];
    struct UnkStruct_0208d900 *unk_38;
    char pad1[0x10];
    unsigned char unk_4C;
    char pad2[0x2];
    unsigned char unk_4F;
};

extern struct UnkStruct_0208d900 *func_020a9034(int, int, int);
extern void func_02051694(struct UnkStruct_0208d900 *);

extern unsigned char data_021c81d4[];

void func_0208d900(struct UnkStruct_0208d900_2 *self)
{
    if (self->unk_38 != 0) {
        return;
    }
    self->unk_38 = func_020a9034((self->unk_4F != 0) ? 0xf4 : 0xa8, 2, 1);
    if (self->unk_38 == 0) {
        return;
    }
    self->unk_38->unk_2C = 4;
    self->unk_38->unk_50 = 2;
    self->unk_38->unk_55 = 1;
    self->unk_38->unk_39 = 0;
    self->unk_38->unk_38 = 9;
    self->unk_38->unk_28 = (unsigned int) data_021c81d4;
    func_02051694(self->unk_38);
    self->unk_4C = 1;
}
