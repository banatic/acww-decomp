/* func_ov134_0229afec @ 0x0229afec, 0x26 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229afec {
    unsigned char pad_00[0x92];
    unsigned short unk_92;
};
extern int func_ov134_0229aed4(struct UnkStruct_0229afec *self, int a, int b, unsigned short f);
extern void func_ov134_0229accc(struct UnkStruct_0229afec *self, int v);

void func_ov134_0229afec(struct UnkStruct_0229afec *self, int a, int b)
{
    int result = func_ov134_0229aed4(self, a, b, self->unk_92);
    if (result != 0) {
        func_ov134_0229accc(self, (result * 60) >> 16);
    }
}
