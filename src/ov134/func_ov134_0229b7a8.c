/* func_ov134_0229b7a8 @ 0x0229b7a8, 0x2c bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa3];
    unsigned char unk_A3;
    unsigned char pad_A4[0x18];
    unsigned char unk_BC;
} UnkStruct_0229b7a8;

extern void func_ov134_0229b5ac(void *self, unsigned char a, int b, int c, unsigned char d, int e, int f);

void func_ov134_0229b7a8(UnkStruct_0229b7a8 *self)
{
    func_ov134_0229b5ac(self, self->unk_A3, 0x190, 3, self->unk_BC, 15, 0);
}
