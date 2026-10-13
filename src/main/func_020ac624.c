/* func_020ac624 @ 0x020ac624, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020ac478(void *self, int a, int b);
extern void func_020ac470(void *self, int a);
extern void func_020ac89c(unsigned char *dst, int len);
extern void MI_CpuCopy8(unsigned char *dst1, unsigned char *dst2, int len);

typedef struct {
    unsigned char pad_00[4];
    unsigned char *p;
    unsigned char pad_08[0x16];
    unsigned short unk_1E;
} UnkStruct_020ac624;

void func_020ac624(UnkStruct_020ac624 *self)
{
    MI_CpuCopy8(self->p + 0x29e, self->p + 0x39e, 0x22);
    MI_CpuCopy8(self->p + 0x2de, self->p + 0x3de, 0x22);
    MI_CpuCopy8(self->p + 0x25e, self->p + 0x35e, 0x22);
    MI_CpuCopy8(self->p + 0x49e, self->p + 0x41e, 0x22);
    MI_CpuCopy8(self->p + 0x4de, self->p + 0x45e, 0x22);
    MI_CpuCopy8(self->p + 0x51e, self->p + 0x49e, 0x22);
    func_020ac89c(self->p + 0x25e, 0x22);
    func_020ac89c(self->p + 0x29e, 0x22);
    func_020ac89c(self->p + 0x2de, 0x22);
    func_020ac89c(self->p + 0x31e, 0x22);
    func_020ac89c(self->p + 0x4de, 0x22);
    func_020ac89c(self->p + 0x51e, 0x22);
    func_020ac478(self, 0xd, 0x12);
    func_020ac470(self, 0xd);
    self->unk_1E = 2;
}
