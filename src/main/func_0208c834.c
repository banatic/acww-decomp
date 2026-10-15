/* func_0208c834 @ 0x0208c834, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208af30(void *self);
extern char data_020e2250;
extern void func_0208a1f4(void *);
extern void func_0208a1f8(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));

struct UnkStruct_0208c834 {
    void *unk_00;
    unsigned char pad_04[8];
    unsigned char pad_0C[0xb4];
    int unk_C0;
    int unk_C4;
    int unk_C8;
    int unk_CC;
    int unk_D0;
    unsigned char unk_D4;
};

struct UnkStruct_0208c834 *func_0208c834(struct UnkStruct_0208c834 *self)
{
    func_0208af30(self);
    self->unk_00 = &data_020e2250;
    __cxa_vec_ctor((void *) ((char *) self + 0xc), 9, 0x14, (void (*)(void *)) func_0208a1f8,
                   (void (*)(void *)) func_0208a1f4);
    self->unk_C0 = 0;
    self->unk_C4 = 0;
    self->unk_C8 = 0;
    self->unk_CC = 0;
    self->unk_D0 = 0;
    self->unk_D4 = 0;
    return self;
}
