/* func_020f97dc @ 0x020f97dc, 0x6c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,p
 */

extern int FX_Div(int, int);
extern void func_020eed18(int, int, int);
extern int data_021fd1f8;

typedef struct {
    int unk_00;
    int unk_04;
    unsigned char unk_08;
    unsigned char unk_09;
    char pad_0A;
    signed char unk_0B;
    signed char unk_0C;
    char pad_0D;
    short unk_0E;
} UnkStruct_020f97dc;

void func_020f97dc(UnkStruct_020f97dc *self, unsigned char b)
{
    self->unk_08 = b;
    self->unk_0B = -1;
    self->unk_0C = -1;
    self->unk_09 = 0;
    if (self->unk_08) {
        self->unk_0E = 120;
        self->unk_04 = FX_Div(0x258000, self->unk_0E << 12);
        return;
    } else {
        self->unk_0E = 120;
        func_020eed18((int) &data_021fd1f8, 0, 120);
    }
}
