/* func_ov111_0229f598 @ 0x0229f598, 0x24 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov111_0229fd08(void *);
extern void func_ov111_0229f554(void *, int);
extern void func_ov095_0229b3ec(void *);

struct UnkStruct_0229f598 {
    unsigned char pad_00[0xa1];
    char unk_A1;
    unsigned char pad_A2[0xac - 0xa1 - 1];
    char unk_AC;
};

int func_ov111_0229f598(struct UnkStruct_0229f598 *self, int value)
{
    int new_val = value - 0x18;
    self->unk_A1 = new_val;
    func_ov111_0229f554(self, new_val);
    func_ov095_0229b3ec(&self->unk_AC);
    return func_ov111_0229fd08(self);
}
