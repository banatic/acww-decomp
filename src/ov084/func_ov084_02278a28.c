/* func_ov084_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov084_022794ac;
extern void func_ov084_02278fa4(void *);
extern void func_0202ee5c(void *);
extern void func_020edf54(void *);

struct UnkStruct_02278a28 {
    void *unk_00;
    char pad_04[0x654];
    char sub[1];
};

struct UnkStruct_02278a28 *func_ov084_02278a28(struct UnkStruct_02278a28 *self)
{
    self->unk_00 = &data_ov084_022794ac;
    func_ov084_02278fa4(self->sub);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
