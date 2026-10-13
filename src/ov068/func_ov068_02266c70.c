/* func_ov068_02266c70 @ 0x02266c70, 0x40 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_02266be4(void *p, int a, int b, int c, int d, int e, int f, int g, int h);
extern int data_020c814c;

struct UnkStruct_02266c70 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    short unk_14;
};

extern unsigned char data_021fbee8[];

void func_ov068_02266c70(struct UnkStruct_02266c70 *self, int arg1)
{
    self->unk_00 = 0;
    func_ov068_02266be4(self, arg1, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    self->unk_04 = 2;
    self->unk_0C = -1;
    self->unk_10 = -1;
    self->unk_14 = 0;
}
