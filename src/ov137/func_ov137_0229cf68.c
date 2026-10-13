/* func_ov137_0229cf68 @ 0x0229cf68, 0x38 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov134_0229bd38(void *addr, int a, int b, int c, int d);

struct UnkStruct_0229cf68 {
    char pad_00[0x2c4];
    unsigned char unk_2C4;
    char pad_2C5[0x2b74 - 0x2c4 - 1];
    unsigned short unk_2B74;
    char pad_2B76[1];
    unsigned char unk_2B77;
};

void func_ov137_0229cf68(struct UnkStruct_0229cf68 *self)
{
    func_ov134_0229bd38(&self->unk_2C4, 2, 6, 4, 3);
    self->unk_2B77 = 0;
    self->unk_2B74 = 0;
}
