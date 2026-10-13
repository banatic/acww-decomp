/* func_ov048_022626f0 @ 0x022626f0, 0x48 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_02088264(void *);
extern void func_0203f5dc(void *);
extern void func_0203f664(void *);
extern void func_02072da4(void *);
extern void func_0201615c(void *);
extern char data_ov048_02264208[];

struct UnkStruct_022626f0 {
    void *unk_00;
    char pad_04[0xb8];
    char sub_bc;
    char pad_BD[0x333];
    char sub_3f0;
    char pad_3F1[0x113];
    char sub_504;
    char pad_505[0xd3];
    char sub_5d8;
};

struct UnkStruct_022626f0 *func_ov048_022626f0(struct UnkStruct_022626f0 *self)
{
    self->unk_00 = data_ov048_02264208;
    func_02088264(&self->sub_5d8);
    func_0203f5dc(&self->sub_504);
    func_0203f664(&self->sub_3f0);
    func_02072da4(&self->sub_bc);
    func_0201615c(self);
    return self;
}
