/* func_ov096_0229e82c @ 0x0229e82c, 0x6c bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb4];
    unsigned char unk_B4;
    unsigned char pad_B5[4];
    unsigned char unk_B9;
} UnkStruct_0229e82c;

extern int func_ov096_0229ee80(UnkStruct_0229e82c *self, unsigned char val);
extern void func_ov096_0229e898(UnkStruct_0229e82c *self, unsigned char val, int arg);
extern int func_ov096_0229f0dc(UnkStruct_0229e82c *self, unsigned char val);
extern int func_ov096_0229f088(UnkStruct_0229e82c *self, unsigned char val);
extern void func_ov096_0229f5e0(UnkStruct_0229e82c *self, unsigned char val, int a, int b);

void func_ov096_0229e82c(UnkStruct_0229e82c *self, int arg)
{
    if (func_ov096_0229ee80(self, self->unk_B4) != 0) {
        goto if_part;
    }
    {
        unsigned char *p = &self->unk_B4;
        func_ov096_0229e898(self, *p, arg);
    }
    goto end;
if_part:
    if (self->unk_B9 != 0x26) {
        int a = func_ov096_0229f0dc(self, self->unk_B9);
        int b = func_ov096_0229f088(self, self->unk_B9);
        func_ov096_0229e898(self, self->unk_B9, 1);
        func_ov096_0229f5e0(self, self->unk_B4, a, b);
        self->unk_B9 = 0x26;
    }
end:
    return;
}