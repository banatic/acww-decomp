/* func_020ac50c @ 0x020ac50c, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int pad_00;
    unsigned char *data;
    unsigned char pad_08[0x1e - 0x08];
    unsigned short unk_1E;
} UnkStruct_020ac50c;

extern void MI_CpuCopy8(void *dest, const void *src, unsigned int size);
extern void func_020ac89c(void *dest, unsigned int size);
extern void func_020ac478(UnkStruct_020ac50c *self, int a, int b);
extern void func_020ac470(UnkStruct_020ac50c *self, int a);

void func_020ac50c(UnkStruct_020ac50c *self)
{
    MI_CpuCopy8(self->data + 0x29e, self->data + 0x31e, 0x22);
    MI_CpuCopy8(self->data + 0x2de, self->data + 0x35e, 0x22);
    MI_CpuCopy8(self->data + 0x25e, self->data + 0x2de, 0x22);
    func_020ac89c(self->data + 0x25e, 0x22);
    func_020ac89c(self->data + 0x29e, 0x22);
    func_020ac478(self, 0xb, 0x14);
    func_020ac470(self, 0xb);
    self->unk_1E = 4;
}
