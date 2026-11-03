/* turtle_gardens_talk_2: 3 functions, module ov083
 * mwccarm 1.2/base -O4,s
 * func_ov083_02278d7c @ 0x02278d7c, 0x24 bytes, Thumb
 * func_ov083_02278d64 @ 0x02278d64, 0x18 bytes, Thumb
 * func_ov083_02278d44 @ 0x02278d44, 0x20 bytes, Thumb
 */

typedef struct {
    void *unk_00;
    unsigned char pad_04[0xb8 - 4];
    unsigned short unk_B8;
} UnkStruct_02278d7c;

struct UnkStruct_02278d64 {
    struct UnkStruct_02278d64 *unk_00;
};

typedef struct UnkStruct_02278d44 {
    void *unk_00;
} UnkStruct_02278d44;

extern void *func_0202eb70(UnkStruct_02278d7c *self);
extern char data_ov083_022791fc;
extern void *func_0202eb20(struct UnkStruct_02278d64 *self);
extern void func_020edb3c(UnkStruct_02278d44 *self);

UnkStruct_02278d7c *func_ov083_02278d7c(UnkStruct_02278d7c *self)
{
    func_0202eb70(self);
    self->unk_00 = &data_ov083_022791fc;
    self->unk_B8 = 0xfff1;
    return self;
}

struct UnkStruct_02278d64 *func_ov083_02278d64(struct UnkStruct_02278d64 *self)
{
    self->unk_00 = ((struct UnkStruct_02278d64 *) &data_ov083_022791fc);
    func_0202eb20(self);
    return self;
}

UnkStruct_02278d44 *func_ov083_02278d44(UnkStruct_02278d44 *self)
{
    self->unk_00 = ((int *) &data_ov083_022791fc);
    func_0202eb20((struct UnkStruct_02278d64 *) self);
    func_020edb3c(self);
    return self;
}
