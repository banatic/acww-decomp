/* func_ov111_022a0b20 @ 0x022a0b20, 0x38 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229afa4(void *);
extern void func_ov111_0229f084(void *);

typedef struct {
    unsigned char pad_00[0xa2];
    volatile unsigned char unk_A2;
    unsigned char pad_A3[9];
    unsigned char unk_AC;
} UnkStruct_022a0b20;

void func_ov111_022a0b20(UnkStruct_022a0b20 *self)
{
    if (self->unk_A2) {
        self->unk_A2 = self->unk_A2 - 1;
        if (self->unk_A2 == 0) {
            func_ov095_0229afa4(&self->unk_AC);
        }
    }
    func_ov111_0229f084(self);
}
