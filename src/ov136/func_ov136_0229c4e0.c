/* func_ov136_0229c4e0 @ 0x0229c4e0, 0x38 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c4e0 {
    int pad_00;
};
struct UnkStruct_0229c4e0_2 {
    void *vtbl;
    char pad_04[0x90];
    struct UnkStruct_0229c4e0 sub1;
    char pad_98[0x60];
    struct UnkStruct_0229c4e0 sub2;
    char pad_FC[0x1c8];
    struct UnkStruct_0229c4e0 sub3;
};

extern void func_ov134_0229beb0(struct UnkStruct_0229c4e0 *p);
extern void func_ov002_0220afdc(struct UnkStruct_0229c4e0 *p);
extern void func_ov002_02209cb4(struct UnkStruct_0229c4e0 *p);
extern void func_ov002_0220826c(struct UnkStruct_0229c4e0_2 *p);

extern unsigned char data_ov136_0229d510[];

struct UnkStruct_0229c4e0_2 *func_ov136_0229c4e0(struct UnkStruct_0229c4e0_2 *self)
{
    self->vtbl = (void *) data_ov136_0229d510;
    func_ov134_0229beb0(&self->sub3);
    func_ov002_0220afdc(&self->sub2);
    func_ov002_02209cb4(&self->sub1);
    func_ov002_0220826c(self);
    return self;
}
