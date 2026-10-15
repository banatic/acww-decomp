/* func_ov083_02278d7c @ 0x02278d7c, 0x24 bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *unk_00;
    unsigned char pad_04[0xb8 - 4];
    unsigned short unk_B8;
} UnkStruct_02278d7c;

extern void *func_0202eb70(UnkStruct_02278d7c *self);
extern char data_ov083_022791fc;

UnkStruct_02278d7c *func_ov083_02278d7c(UnkStruct_02278d7c *self)
{
    func_0202eb70(self);
    self->unk_00 = &data_ov083_022791fc;
    self->unk_B8 = 0xfff1;
    return self;
}
