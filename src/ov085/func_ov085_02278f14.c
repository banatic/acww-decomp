/* func_ov085_02278f14 @ 0x02278f14, 0x18 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb70(void *self);
extern char data_ov085_0227945c;

struct obj_ov085_02278f14 {
    void *unk_00;
};

struct obj_ov085_02278f14 *func_ov085_02278f14(struct obj_ov085_02278f14 *self)
{
    func_0202eb70(self);
    self->unk_00 = (void *) &data_ov085_0227945c;
    return self;
}
