/* func_ov002_02208458 @ 0x02208458, 0x40 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xc];
    unsigned int unk_0C;
    unsigned int unk_10;
    unsigned int unk_14;
    unsigned char unk_18;
} UnkStruct_02208458;

extern void func_ov002_0220882c(UnkStruct_02208458 *self, unsigned int denominator);

void func_ov002_02208458(UnkStruct_02208458 *self, int arg1, unsigned char byte, unsigned int word)
{
    self->unk_18 = byte;
    self->unk_14 = word;
    func_ov002_0220882c(self, (unsigned int) arg1);
    {
        unsigned char val = self->unk_18;
        switch (val) {
            case 0:
            case 1:
                self->unk_0C = 0xC0;
                self->unk_10 = 0xC0;
                break;
            case 2:
            case 3:
                self->unk_0C = 0x100;
                self->unk_10 = 0x100;
                break;
        }
    }
}
