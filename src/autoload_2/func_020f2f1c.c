/* func_020f2f1c @ 0x020f2f1c, 0x38 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

extern int data_0213ecdc;

struct Func020f2f1c {
    int unk_00;
    int unk_04;
    char sub[1];
};

extern void func_020f95f8(void *);
extern void func_020f4514(void *);
extern void func_020edb3c(void *);

struct Func020f2f1c *func_020f2f1c(struct Func020f2f1c *self)
{
    self->unk_00 = (int) &data_0213ecdc;
    func_020f95f8(self->sub);
    func_020f4514(self);
    func_020edb3c(self);
    return self;
}
