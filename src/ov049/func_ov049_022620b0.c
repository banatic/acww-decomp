/* func_ov049_022620b0 @ 0x022620b0, 0x20 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0202eb20(void *);
extern void func_020edb3c(void *);

struct UnkStruct_022620b0 {
    void *unk_00;
};

extern unsigned char data_ov049_022634b4[];

void *func_ov049_022620b0(struct UnkStruct_022620b0 *self)
{
    self->unk_00 = (void *) data_ov049_022634b4;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
