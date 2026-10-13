/* func_ov137_0229d2f4 @ 0x0229d2f4, 0x1e bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov137_0229cf68(void *self);
extern void func_ov002_022080a0(void *self);

typedef struct {
    char pad_00[0x8c];
    unsigned char unk_8C;
} UnkStruct_0229d2f4;

int func_ov137_0229d2f4(UnkStruct_0229d2f4 *self)
{
    func_ov137_0229cf68(self);
    self->unk_8C = 0;
    func_ov002_022080a0(self);
    return 1;
}
