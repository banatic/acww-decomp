/* func_ov075_02278e44 @ 0x02278e44, 0x88 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern int gt2GetIncomingBufferSize(void *);
extern void func_0201ad18(void *, int, int, int, int, int, int, int);
extern int func_0201c314(void *, int);
extern int func_020147fc(void *, int, int, int);
extern int data_020c814c;

struct UnkStruct_02278e44 {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x3b0 - 0x90];
    char unk_3B0[0x4e8 - 0x3b0];
    int unk_4E8;
    char pad_4EC[0x618 - 0x4ec];
    char unk_618[0x658 - 0x618];
    char unk_658[0x718 - 0x658];
    unsigned char unk_718;
};

extern unsigned char data_021fbee8[];

int func_ov075_02278e44(struct UnkStruct_02278e44 *self)
{
    int result = gt2GetIncomingBufferSize(self->unk_658);
    int s = self->unk_8E;
    if (self->unk_718 != 0) {
        func_0201ad18(self->unk_3B0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
        self->unk_4E8 &= ~2;
    }
    if (result != 0) {
        s = func_0201c314(self, result);
    }
    func_020147fc(self->unk_618, 0, s, 0);
    return 1;
}
