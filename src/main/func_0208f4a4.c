/* func_0208f4a4 @ 0x0208f4a4, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208effc(void *);
extern void *func_0208f628(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);

struct UnkStruct_0208f4a4 {
    void *vtable;
    char pad_04[0x18];
    char sub1c[0x14];
    char sub30[0x1c];
    char sub4c[1];
};

extern unsigned char data_020e23a0[];

struct UnkStruct_0208f4a4 *func_0208f4a4(struct UnkStruct_0208f4a4 *self)
{
    self->vtable = (void *) data_020e23a0;
    func_0208effc(self);
    func_0208f628(&self->sub4c);
    func_0208a1f4(&self->sub30);
    func_0208a1f4(&self->sub1c);
    func_0208af00(self);
    func_020edb3c(self);
    return self;
}
