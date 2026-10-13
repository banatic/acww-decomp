/* func_02035f50 @ 0x02035f50, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02035f50 {
    void *unk_00;
    unsigned int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    unsigned char unk_0A;
    unsigned char unk_0B;
    unsigned int unk_0C;
    unsigned int unk_10;
};

extern unsigned char data_020da2d4[];

void func_02035f50(struct UnkStruct_02035f50 *self, unsigned int arg)
{
    self->unk_00 = (void *) data_020da2d4;
    self->unk_04 = arg;
    self->unk_08 = 0;
    self->unk_09 = 0;
    self->unk_0A = 0;
    self->unk_0B = 0;
    self->unk_0C = 0;
    self->unk_10 = 0;
}
