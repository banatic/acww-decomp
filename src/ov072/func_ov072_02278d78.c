/* func_ov072_02278d78 @ 0x02278d78, 0x20 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

struct Class {
    void *vt;
};

extern void *func_0202eb20(struct Class *self);
extern void func_020edb3c(struct Class *self);
extern int data_ov072_02279a78;

struct Class *func_ov072_02278d78(struct Class *self)
{
    self->vt = &data_ov072_02279a78;
    func_0202eb20(self);
    func_020edb3c(self);
    return self;
}
