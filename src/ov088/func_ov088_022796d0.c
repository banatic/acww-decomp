/* func_ov088_022796d0 @ 0x022796d0, 0x80 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_022796d0 {
    char pad_00[0x3b0];
    char unk_3B0;
    char pad_3B1[0x1a7];
    char unk_558;
    char pad_559[0xb];
    char unk_564;
    char pad_565[0x1d3];
    char unk_738;
} UnkStruct_022796d0;

extern unsigned short data_020c80f8;
extern unsigned int data_020c814c;
extern char data_021fbee8[];

int func_02019d0c(void *a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k);
void func_02013c0c(void *a);
void func_0201ad18(void *a, int b, int c, int d, int e, int f, int g, int h);

int func_ov088_022796d0(UnkStruct_022796d0 *self)
{
    self->unk_738 = 0;
    func_02019d0c(&self->unk_564, 0, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    func_02013c0c(&self->unk_558);
    func_02013c0c(&self->unk_558);
    func_0201ad18(&self->unk_3B0, 1, 0, 0, (unsigned int) data_021fbee8, 4, data_020c814c, 1);
    return 1;
}
