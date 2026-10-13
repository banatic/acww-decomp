/* func_ov079_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov079_0227a104;
extern void func_ov079_02278d1c(void *p);
extern void func_0202ee5c(void *p);
extern void func_020edf54(void *p);

struct UnkStruct_02278a28 {
    int *unk_00;
    char pad_04[0x654];
    int unk_658;
};

struct UnkStruct_02278a28 *func_ov079_02278a28(struct UnkStruct_02278a28 *self)
{
    self->unk_00 = &data_ov079_0227a104;
    func_ov079_02278d1c((void *) &self->unk_658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
