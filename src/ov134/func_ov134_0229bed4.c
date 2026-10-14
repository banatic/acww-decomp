/* func_ov134_0229bed4 @ 0x0229bed4, 0x88 bytes, Thumb, module ov134
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a5fc(void *p);
extern void func_020b9cfc(void *p);
extern void __cxa_vec_ctor(void *p, int a, int b, void (*cb1)(void), void (*cb2)(void));
extern void func_02070be8(void);
extern void func_02070c08(void);

typedef struct {
    char pad_00[0x18];
    char sub18[0xa0];
    int zeros[8];
    char subD8[0x804 - 0xd8];
    char unk_804;
    char pad_805[0x828 - 0x805];
    char unk_828;
    char pad_829[0x84c - 0x829];
    char unk_84C;
} UnkStruct_0229bed4;

void *func_ov134_0229bed4(UnkStruct_0229bed4 *self)
{
    func_ov002_0220a5fc(self->sub18);
    self->zeros[0] = 0;
    self->zeros[1] = 0;
    self->zeros[2] = 0;
    self->zeros[3] = 0;
    self->zeros[4] = 0;
    self->zeros[5] = 0;
    self->zeros[6] = 0;
    self->zeros[7] = 0;
    __cxa_vec_ctor(self->subD8, 0x11, 0x6c, func_02070c08, func_02070be8);
    func_020b9cfc(&self->unk_804);
    func_020b9cfc(&self->unk_828);
    func_020b9cfc(&self->unk_84C);
    return self;
}
