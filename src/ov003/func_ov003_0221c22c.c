/* func_ov003_0221c22c @ 0x0221c22c, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_ov009_0226552c(void *unused0);
extern char data_ov003_02238630[];
extern char data_ov003_022386f4[];

typedef struct {
    void *unk_00;
    char pad_04[0xe8];
    void *unk_EC;
} UnkStruct_0221c22c;

UnkStruct_0221c22c *func_ov003_0221c22c(UnkStruct_0221c22c *self)
{
    func_ov009_0226552c(self);
    self->unk_00 = data_ov003_02238630;
    self->unk_EC = data_ov003_022386f4;
    return self;
}
