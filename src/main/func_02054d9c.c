/* func_02054d9c @ 0x02054d9c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020dd0dc;
extern char data_020dd0ec;
extern char data_020dd0fc;

typedef struct {
    void *unk_00;
    unsigned char pad_04[0x98];
    void *unk_9C;
    unsigned char pad_A0[0x18];
    void *unk_B8;
} UnkStruct_02054d9c;

extern void func_02056eb0(void **ptr);
extern void *func_0205517c(UnkStruct_02054d9c *self);

UnkStruct_02054d9c *func_02054d9c(UnkStruct_02054d9c *self)
{
    self->unk_00 = &data_020dd0dc;
    self->unk_9C = &data_020dd0ec;
    self->unk_B8 = &data_020dd0fc;
    func_02056eb0(&self->unk_B8);
    func_0205517c(self);
    return self;
}
