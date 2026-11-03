/* mail_text_6: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0203de48 @ 0x0203de48, 0x1c bytes, Thumb
 * func_0203de30 @ 0x0203de30, 0x18 bytes, Thumb
 * func_0203de10 @ 0x0203de10, 0x20 bytes, Thumb
 * func_0203ddfc @ 0x0203ddfc, 0x14 bytes, Thumb
 * func_0203ddf8 @ 0x0203ddf8, 0x4 bytes, Thumb
 * func_0203ddf0 @ 0x0203ddf0, 0x8 bytes, Thumb
 * func_0203dd9c @ 0x0203dd9c, 0x54 bytes, Thumb
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

extern void *func_020a9a90(void *, unsigned int);
extern char data_020da994[];
extern void *func_020a9a40(void *self);
extern void func_020edb3c(void *);
extern void MI_CpuFill8(void *ptr, int value, int size);
extern char data_020da9ac[];
extern char data_020e3e68[];
extern void func_020a8754(void *p);
extern void *func_020a9484(struct UnkStruct_0203dd9c *self);

void *func_0203de48(void *self)
{
    func_020a9a90(self, 0);
    *(char **) self = data_020da994;
    return self;
}

void *func_0203de30(void *self)
{
    *(void **) self = ((int *) data_020da994);
    func_020a9a40(self);
    return self;
}

void *func_0203de10(void *obj)
{
    *(void **) obj = (void *) ((unsigned char *) data_020da994);
    func_020a9a40(obj);
    func_020edb3c(obj);
    return obj;
}

void func_0203ddfc(void *arg0)
{
    MI_CpuFill8((char *) arg0 + 0xa4, 0, 0x200);
}

int func_0203ddf8(int p0)
{
    return ((int) (p0) + (164));
}

int func_0203ddf0(void)
{
    return 512;
}

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
