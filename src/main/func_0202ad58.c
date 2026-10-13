/* func_0202ad58 @ 0x0202ad58, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct SubA {
    unsigned char pad_00[0x824];
    unsigned char unk_824;
    unsigned char pad_825[0xB];
    unsigned int unk_830;
} SubA;

typedef struct UnkStruct_0202ad58 {
    unsigned char pad_00[0x100];
    SubA *sub100;
    char buf104[30];
    unsigned char unk_122;
} UnkStruct_0202ad58;

typedef struct UnkStruct_0202ad58_2 {
    char *p;
    unsigned char b;
} UnkStruct_0202ad58_2;

extern int data_020c8b18;
extern int func_0208150c(unsigned int);
extern int func_020036e8(int);
extern void func_0200368c(char *, int, int, int);

void func_0202ad58(UnkStruct_0202ad58 *self, UnkStruct_0202ad58_2 *out)
{
    int temp;

    temp = func_020036e8(func_0208150c(self->sub100->unk_830));
    func_0200368c(self->buf104, 30, data_020c8b18, temp);

    if (self->sub100->unk_824 == 0) {
        self->unk_122 = 6;
    } else {
        self->unk_122 = 11;
    }

    out->p = self->buf104;
    out->b = self->unk_122;
}
