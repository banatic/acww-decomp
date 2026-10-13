/* func_ov106_0229eadc @ 0x0229eadc, 0x20 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f54(void *p);

struct UnkStruct_0229eadc {
    char pad_00[0x9c];
    int unk_9C;
};

void func_ov106_0229eadc(struct UnkStruct_0229eadc *self)
{
    func_ov002_02207e80(self, 4, 0, ~0xf);
    self->unk_9C = func_ov002_02207f54(self);
}
