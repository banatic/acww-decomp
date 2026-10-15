/* func_ov003_0221eea0 @ 0x0221eea0, 0x24 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221eea0 {
    unsigned int unk_00;
    unsigned char pad_04[0xE8];
    unsigned int unk_EC;
};

extern void *func_ov009_0226539c(struct UnkStruct_0221eea0 *obj);

extern unsigned char data_ov003_022398e8[];
extern unsigned char data_ov003_022399ac[];

void *func_ov003_0221eea0(struct UnkStruct_0221eea0 *obj)
{
    struct UnkStruct_0221eea0 *self = obj;
    self->unk_00 = (unsigned int) data_ov003_022398e8;
    self->unk_EC = (unsigned int) data_ov003_022399ac;
    func_ov009_0226539c(self);
    return self;
}
