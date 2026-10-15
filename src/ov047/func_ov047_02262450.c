/* func_ov047_02262450 @ 0x02262450, 0xa4 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019c6c(unsigned char *, int, unsigned short);
extern int func_0202ea40(void *, int *, int);
extern int func_020644cc(int);
extern void func_0201ad18(unsigned char *, int, int, int, char *, int, unsigned long, int);
extern unsigned short data_020c80f8;
extern unsigned long data_020c814c;
extern char data_021fbee8;

typedef struct {
    unsigned char pad_00[0x3b0];
    unsigned char sub_3b0[0x1b4];
    unsigned char buf_564[0x1c8];
    unsigned char flag_72c;
    unsigned char pad_72D;
    unsigned short unk_72E;
    unsigned short unk_730;
    unsigned short unk_732;
    unsigned char pad_734[2];
    unsigned char flag_736;
} UnkStruct_02262450;

int func_ov047_02262450(UnkStruct_02262450 *self)
{
    int local;

    self->unk_72E = 0xff;
    func_02019c6c(self->buf_564, 1, self->unk_730);

    if (self->flag_72c == 0) {
        if (func_0202ea40(self, &local, 1) != 0) {
            self->unk_72E = 100 + 20 * func_020644cc(5);
        }
    }

    self->flag_736 = 0;
    self->unk_730 = data_020c80f8;
    self->unk_732 = 0x78;
    func_0201ad18(self->sub_3b0, 1, 0, 0, &data_021fbee8, 4, data_020c814c, 1);
    return 1;
}
