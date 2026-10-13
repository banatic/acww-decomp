/* func_ov139_02299a80 @ 0x02299a80, 0x40 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02299a80 {
    char pad_00[0x93c];
    char unk_93C;
    char pad_93D[0x980 - 0x93c - 1];
    char unk_980;
    char pad_981[0x9a2 - 0x980 - 1];
    unsigned char unk_9A2;
};

extern int func_ov139_022995c0(void *ptr, int n);
extern int func_020b9b6c(void *ptr0, void *ptr1, unsigned char byte, int n);
extern void func_ov139_022995a0(void *ptr, int n);

void func_ov139_02299a80(struct UnkStruct_02299a80 *self)
{
    if (func_ov139_022995c0(self, 1) != 0) {
        if (func_020b9b6c(&self->unk_93C, &self->unk_980, self->unk_9A2, 7) != 0) {
            func_ov139_022995a0(self, 1);
        }
    }
}
