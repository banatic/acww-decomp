/* func_ov082_0227907c @ 0x0227907c, 0x24 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0227907c {
    void *unk_00;
    unsigned char pad_04[0xC0];
    unsigned short unk_C4;
};

extern void func_0202eb70(struct UnkStruct_0227907c *self);

extern unsigned char data_ov082_0227978c[];

struct UnkStruct_0227907c *func_ov082_0227907c(struct UnkStruct_0227907c *self)
{
    func_0202eb70(self);
    self->unk_00 = (void *) data_ov082_0227978c;
    self->unk_C4 = 0xFFF1;
    return self;
}
