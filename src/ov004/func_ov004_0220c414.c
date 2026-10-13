/* func_ov004_0220c414 @ 0x0220c414, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov004_0224fc4c;
extern char data_ov004_0224fcc0;
extern void func_020b82d0(void *addr);
extern void func_020324c4(void *addr);
extern void func_02066994(void *addr);
extern void func_0203f080(void *addr);

struct UnkStruct_0220c414 {
    void *unk_00;
    unsigned char pad_04[0xE8];
    void *unk_EC;
    unsigned char pad_F0[0x48];
    char sub_138;
    unsigned char pad_139[0x9B];
    char sub_1D4;
};

struct UnkStruct_0220c414 *func_ov004_0220c414(struct UnkStruct_0220c414 *self)
{
    self->unk_00 = &data_ov004_0224fc4c;
    self->unk_EC = &data_ov004_0224fcc0;
    func_020b82d0(&self->sub_1D4);
    func_020324c4(&self->sub_138);
    func_02066994(&self->unk_EC);
    func_0203f080(self);
    return self;
}
