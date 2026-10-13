/* func_020f2540 @ 0x020f2540, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ef4c;

struct obj_020f2540 {
    void *unk_00;
};

extern void func_020f4514(struct obj_020f2540 *);
extern void func_020edb3c(struct obj_020f2540 *);

struct obj_020f2540 *func_020f2540(struct obj_020f2540 *self)
{
    self->unk_00 = &data_0213ef4c;
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}
