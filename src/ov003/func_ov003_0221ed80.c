/* func_ov003_0221ed80 @ 0x0221ed80, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_02239754;
extern int data_ov003_02239818;

extern void *func_ov009_0226539c(void *p);
extern void func_020edf54(void *p);

struct func_ov003_0221ed80_obj {
    int *unk_00;
    char pad_04[0xe8];
    int *unk_EC;
};

void *func_ov003_0221ed80(struct func_ov003_0221ed80_obj *self)
{
    self->unk_00 = &data_ov003_02239754;
    self->unk_EC = &data_ov003_02239818;
    func_ov009_0226539c(self);
    func_020edf54(self);
    return self;
}
