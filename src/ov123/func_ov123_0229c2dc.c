/* func_ov123_0229c2dc @ 0x0229c2dc, 0x30 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e9c(void *, int, int);
extern void func_ov002_02208090(void *, int);
extern void func_ov123_02299640(void *, unsigned int);

typedef struct {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_0229c2dc;

void func_ov123_0229c2dc(UnkStruct_0229c2dc *self)
{
    int zero = 0;
    func_ov002_02207e9c(self, zero, zero);
    func_ov002_02208090(self, 7);
    self->unk_98 = 0;
    func_ov123_02299640(self, 0x400);
}
