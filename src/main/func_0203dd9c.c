/* func_0203dd9c @ 0x0203dd9c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0203dd9c {
    void *vtable;
    int pad_04;
    int pad_08;
    int pad_0C;
    int pad_10;
    int pad_14;
    int pad_18;
    int pad_1C;
    int pad_20;
    int value;
    char data[0x14];
    int unk_3C;
    int unk_40;
    char unk_44;
    char unk_45;
    int unk_48;
    int unk_4C;
    char unk_50;
    int unk_54;
    int unk_58;
};

extern char data_020da9ac[];
extern char data_020e3e68[];
extern void func_020a8754(void *p);
extern void *func_020a9484(struct UnkStruct_0203dd9c *self);

struct UnkStruct_0203dd9c *func_0203dd9c(struct UnkStruct_0203dd9c *self, int n)
{
    func_020a9484(self);
    self->vtable = data_020e3e68;
    self->vtable = data_020da9ac;
    self->value = n;
    func_020a8754(self->data);
    self->unk_3C = 0;
    self->unk_40 = 0;
    self->unk_44 = 1;
    self->unk_45 = 0;
    self->unk_48 = 0;
    self->unk_4C = 0;
    self->unk_50 = 0;
    self->unk_54 = 0;
    self->unk_58 = 0;
    return self;
}
