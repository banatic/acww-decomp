/* func_02095158 @ 0x02095158, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void MI_CpuCopy8(const void *src, void *dest, unsigned int size);
extern void func_020642d0(void *self, void *ptr);
extern char data_021dc7aa;

typedef struct {
    unsigned char pad_00[0x0E];
    unsigned short unk_0E;
    unsigned char data[0x0C];
    unsigned char unk_1C;
} UnkStruct_02095158;

void func_02095158(UnkStruct_02095158 *self, void *src, unsigned short val1, unsigned char val2, void *ptr)
{
    MI_CpuCopy8(src, self->data, 12);
    self->unk_0E = val1;
    self->unk_1C = val2;
    if (ptr == 0) {
        ptr = &data_021dc7aa;
    }
    func_020642d0(self, ptr);
}
