/* func_ov003_0221c1dc @ 0x0221c1dc, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov003_02238630;
extern unsigned int data_ov003_022386f4;
extern void *func_ov009_0226539c(void *self);
extern void func_020edf54(void *self);

typedef struct {
    unsigned int unk_00;
    unsigned char pad_04[0xe8];
    unsigned int unk_EC;
} UnkStruct_0221c1dc;

UnkStruct_0221c1dc *func_ov003_0221c1dc(UnkStruct_0221c1dc *self)
{
    self->unk_00 = (unsigned int) &data_ov003_02238630;
    self->unk_EC = (unsigned int) &data_ov003_022386f4;
    func_ov009_0226539c(self);
    func_020edf54(self);
    return self;
}
