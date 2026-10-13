/* func_ov134_0229ba10 @ 0x0229ba10, 0xdc bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa2];
    unsigned char unk_A2;
    unsigned char unk_A3;
} UnkStruct_0229ba10;

extern void func_ov134_0229b63c(void *self, unsigned char v1, unsigned int v2, unsigned int v3, unsigned int v4,
                                unsigned int v5, unsigned int v6, unsigned int v7);
extern void func_ov134_0229b8dc(void *self);

void func_ov134_0229ba10(UnkStruct_0229ba10 *self, unsigned int param)
{
    func_ov134_0229b63c(self, self->unk_A3, 0x18a, 3, 0xb2, 0, 0xf, 0);
    func_ov134_0229b63c(self, self->unk_A3, 0x196, 3, 0xb3, 0, 0xf, 0);
    func_ov134_0229b63c(self, self->unk_A3, 0x1a2, 3, 0xb4, 0, 0xf, 0);
    func_ov134_0229b63c(self, self->unk_A3, 0x1bc, 3, 0xb5, 0, 0xf, 0);
    func_ov134_0229b63c(self, self->unk_A3, 0x1c8, 3, 0xb6, 0, 0xf, 0);
    func_ov134_0229b8dc(self);
    func_ov134_0229b63c(self, self->unk_A2, 0x54, 0x10, param, 1, 0xf, 0xe);
}
