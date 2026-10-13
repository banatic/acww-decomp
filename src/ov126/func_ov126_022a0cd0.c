/* func_ov126_022a0cd0 @ 0x022a0cd0, 0x30 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(void *, unsigned char);
extern void func_ov126_022a0978(void *);

typedef struct {
    char pad_00[0xae];
    unsigned char unk_AE;
} UnkStruct_022a0cd0;

void func_ov126_022a0cd0(UnkStruct_022a0cd0 *self)
{
    if ((data_021fbe40 & 0x100) != 0) {
        return;
    }
    func_ov002_02208098(self, self->unk_AE);
    func_ov126_022a0978(self);
}
