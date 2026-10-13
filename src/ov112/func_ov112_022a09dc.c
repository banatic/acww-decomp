/* func_ov112_022a09dc @ 0x022a09dc, 0x30 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xc1];
    unsigned char byte_at_c1;
} UnkStruct_022a09dc;

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(UnkStruct_022a09dc *self, unsigned char byte);
extern void func_ov112_0229f488(UnkStruct_022a09dc *self);

void func_ov112_022a09dc(UnkStruct_022a09dc *self)
{
    if (!(data_021fbe40 & 0x100)) {
        func_ov002_02208098(self, self->byte_at_c1);
        func_ov112_0229f488(self);
    }
}
