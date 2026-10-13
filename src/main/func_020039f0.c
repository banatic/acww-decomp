/* func_020039f0 @ 0x020039f0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern signed char data_020c7588[];
extern void func_0200396c(void *obj, int flag);

struct UnkStruct_020039f0 {
    unsigned char pad_00[0x20];
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
    unsigned char unk_30;
    unsigned char unk_31;
    unsigned char unk_32;
    unsigned char unk_33;
    int unk_34;
    int unk_38;
    int unk_3C;
};

void func_020039f0(struct UnkStruct_020039f0 *self)
{
    self->unk_31 = 0;
    self->unk_20 = data_020c7588[0];
    self->unk_24 = 0;
    self->unk_28 = 0;
    self->unk_2C = 0;
    self->unk_30 = 0;
    self->unk_32 = 1;
    func_0200396c(self, 0);
    self->unk_33 = 0;
    self->unk_34 = 0;
    self->unk_38 = 5;
    self->unk_3C = 0;
}
