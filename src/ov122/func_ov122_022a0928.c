/* func_ov122_022a0928 @ 0x022a0928, 0x4c bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(void *self, unsigned char byte);
extern int func_ov095_0229bf0c(void *ptr);
extern void func_ov122_022a0be4(void *self, int value);
extern int func_ov122_0229efe8(void *self, int value);
extern void func_ov122_0229f1b4(void *self);

typedef struct UnkStruct_022a0928 {
    char pad_00[0xb4];
    unsigned char unk_B4;
    char pad_B5[0x0b];
    char unk_C0;
} UnkStruct_022a0928;

void func_ov122_022a0928(UnkStruct_022a0928 *self)
{
    if ((data_021fbe40 & 2) == 0) {
        func_ov002_02208098(self, self->unk_B4);
    } else {
        if (func_ov095_0229bf0c(&self->unk_C0) != 0) {
            func_ov122_022a0be4(self, 0x100);
            if (func_ov122_0229efe8(self, 0x100) != 0) {
                func_ov122_0229f1b4(self);
            }
        }
    }
}
