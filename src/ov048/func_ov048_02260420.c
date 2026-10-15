/* func_ov048_02260420 @ 0x02260420, 0x28 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_ov048_02264298;
extern void *func_ov048_022626f0(void *ptr);
extern void *func_0202ee5c(void *ptr);

struct UnkStruct_02260420 {
    unsigned int unk_00;
};

struct UnkStruct_02260420 *func_ov048_02260420(struct UnkStruct_02260420 *self)
{
    self->unk_00 = (unsigned int) &data_ov048_02264298;
    func_ov048_022626f0((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
