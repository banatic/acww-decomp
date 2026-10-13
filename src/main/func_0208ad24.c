/* func_0208ad24 @ 0x0208ad24, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a4dc(void *);
extern void func_0208aeb8(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern char data_020e20ac;

struct UnkStruct_0208ad24 {
    void *unk_00;
};

struct UnkStruct_0208ad24 *func_0208ad24(struct UnkStruct_0208ad24 *self)
{
    self->unk_00 = &data_020e20ac;
    func_0208a4dc(self);
    func_0208aeb8((char *) self + 0x90);
    func_0208aeb8((char *) self + 0x60);
    func_0208a1f4((char *) self + 0x20);
    func_0208a1f4((char *) self + 0xc);
    func_0208af00(self);
    return self;
}
