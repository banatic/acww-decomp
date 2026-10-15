/* func_ov082_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov082_0227981c[];

struct Struct_ov082_02278a28 {
    char *unk_00;
    char pad_04[0x654];
    char unk_658;
};

extern void *func_ov082_02279064(char *p);
extern void *func_0202ee5c(struct Struct_ov082_02278a28 *self);
extern void func_020edf54(struct Struct_ov082_02278a28 *self);

struct Struct_ov082_02278a28 *func_ov082_02278a28(struct Struct_ov082_02278a28 *self)
{
    self->unk_00 = data_ov082_0227981c;
    func_ov082_02279064(&self->unk_658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
