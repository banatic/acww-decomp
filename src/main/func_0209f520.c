/* func_0209f520 @ 0x0209f520, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02066994(void *);
extern unsigned char data_020e3758;

struct Obj0209f520 {
    void *unk_00;
};

struct Obj0209f520 *func_0209f520(struct Obj0209f520 *self)
{
    self->unk_00 = &data_020e3758;
    func_02066994(self);
    return self;
}
