/* func_020b5630 @ 0x020b5630, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8cac(void *);
extern void func_020a8c1c(void *);
extern int data_020e5218;

struct obj {
    void *unk_00;
};

struct obj *func_020b5630(struct obj *self)
{
    func_020a8cac(self);
    self->unk_00 = &data_020e5218;
    func_020a8c1c(self);
    return self;
}
