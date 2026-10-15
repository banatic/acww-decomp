/* func_ov122_022a0204 @ 0x022a0204, 0x48 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern int func_ov122_022a0be4(void *self, int mode);
extern void func_ov095_0229bf3c(void *ptr);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

typedef struct {
    unsigned char pad_00[0x8d];
    unsigned char byte_b0;
    unsigned char pad_8E[0x26];
    unsigned char unk_B4;
} UnkStruct_022a0204;

int func_ov122_022a0204(UnkStruct_022a0204 *self)
{
    if (!(data_021fbe40 & 2)) {
        return 0;
    }
    func_ov122_022a0be4(self, 0x100);
    func_ov095_0229bf3c((char *) self + 0xc0);
    self->unk_B4 = self->byte_b0;
    func_ov002_02208098((void *) (self), 0xb);
    return 1;
}
