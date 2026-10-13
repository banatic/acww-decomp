/* func_ov104_0229eb48 @ 0x0229eb48, 0x20 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x9C];
    int value;
} UnkStruct_0229eb48;

extern void func_ov002_02207e80(UnkStruct_0229eb48 *obj, int a, int b, int c);
extern int func_ov002_02207f54(UnkStruct_0229eb48 *obj);

void func_ov104_0229eb48(UnkStruct_0229eb48 *self)
{
    func_ov002_02207e80(self, 4, 0, ~0xf);
    self->value = func_ov002_02207f54(self);
}
