/* func_ov087_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02278a28 {
    char pad_00;
};
extern void func_ov087_02278fdc(struct UnkStruct_02278a28 *p);
extern void func_0202ee5c(void *p);
extern void func_020edf54(void *p);
extern char data_ov087_022794ec;

struct UnkStruct_02278a28_2 {
    void *unk_00;
    char pad_04[0x654];
    struct UnkStruct_02278a28 sub;
};

struct UnkStruct_02278a28_2 *func_ov087_02278a28(struct UnkStruct_02278a28_2 *self)
{
    self->unk_00 = &data_ov087_022794ec;
    func_ov087_02278fdc(&self->sub);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
