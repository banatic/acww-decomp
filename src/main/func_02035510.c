/* func_02035510 @ 0x02035510, 0xa8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x1c0];
    unsigned int unk_1C0;
    unsigned char unk_1C4[0x24c - 0x1c4];
    unsigned char unk_24C[0x264 - 0x24c];
    unsigned char unk_264[0x2a0 - 0x264];
    unsigned char unk_2A0[0x2b4 - 0x2a0];
    unsigned char unk_2B4[0x2d0 - 0x2b4];
    unsigned char unk_2D0[0x2e4 - 0x2d0];
    unsigned char unk_2E4[0x2f0 - 0x2e4];
    unsigned char unk_2F0[0x2f4 - 0x2f0];
    unsigned char unk_2F4;
} UnkStruct_02035510;

extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern int *func_0203652c(void *a, void *b);
extern void func_02037454(void *a);
extern void *func_020369fc(void *a, void *b);
extern void func_02036870(void *a, void *b);
extern void *func_02035ff8(void *a, void *b);
extern void func_02035f50(void *a, void *b);
extern void func_02035b20(void *a, void *b);
extern void func_02035a24(void *a);

extern void func_020374cc(void *);
extern int func_020374fc(void *);

UnkStruct_02035510 *func_02035510(UnkStruct_02035510 *self)
{
    __cxa_vec_ctor((void *) (self), 0x10, 0x1c, (((void (*)(void *)) func_020374fc)), (void (*)(void *)) func_020374cc);
    self->unk_1C0 = 0;
    func_0203652c(self->unk_1C4, self);
    func_02037454(self->unk_24C);
    func_020369fc(self->unk_264, self);
    func_02036870(self->unk_2A0, self);
    func_02035ff8(self->unk_2B4, self);
    func_02035f50(self->unk_2D0, self);
    func_02035b20(self->unk_2E4, self);
    func_02035a24(self->unk_2F0);
    self->unk_2F4 = 0;
    return self;
}
