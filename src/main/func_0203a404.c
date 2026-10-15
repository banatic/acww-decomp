/* func_0203a404 @ 0x0203a404, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a8cac(void *ptr);
extern void func_020a8c1c(void *ptr);
extern char data_020da640;

struct func_0203a404_struct {
    void *unk_00;
};

struct func_0203a404_struct *func_0203a404(struct func_0203a404_struct *self)
{
    func_020a8cac(self);
    self->unk_00 = &data_020da640;
    func_020a8c1c(self);
    return self;
}
