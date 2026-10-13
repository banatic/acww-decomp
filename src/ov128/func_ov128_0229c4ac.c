/* func_ov128_0229c4ac @ 0x0229c4ac, 0x24 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);

typedef struct {
    char pad_00[0x2d50];
    int unk_2D50;
} UnkStruct_0229c4ac;

void func_ov128_0229c4ac(UnkStruct_0229c4ac *self)
{
    func_ov002_02207e80(self, 6, 0, 0);
    self->unk_2D50 = func_ov002_02207f60(self);
}
