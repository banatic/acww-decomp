/* func_ov120_0229abdc @ 0x0229abdc, 0x10 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov120_0229a438(void *obj, int a);

struct S_0229abdc {
    char pad_00[0x9a];
    unsigned short unk_9A;
};

void func_ov120_0229abdc(struct S_0229abdc *self, unsigned short val)
{
    self->unk_9A = val;
    func_ov120_0229a438(self, 0x10);
}
