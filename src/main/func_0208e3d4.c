/* func_0208e3d4 @ 0x0208e3d4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208e2a4(void *);
extern void func_0203a3ec(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern __arm void func_020edb3c(void *);
extern unsigned char data_020e22f8[];

struct Object {
    void *unk_00;
    unsigned char pad_04[0x10];
    void *unk_14;
    unsigned char pad_18[0x20];
    void *unk_38;
};

void *func_0208e3d4(struct Object *self)
{
    self->unk_00 = data_020e22f8;
    func_0208e2a4(self);
    func_0203a3ec(&self->unk_38);
    func_0208a1f4(&self->unk_14);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}
