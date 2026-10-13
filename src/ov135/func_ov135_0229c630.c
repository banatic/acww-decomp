/* func_ov135_0229c630 @ 0x0229c630, 0x24 bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229c630 UnkStruct_0229c630;
struct UnkStruct_0229c630 {
    char pad_00[0x8d];
    unsigned char unk_8D;
    char pad_8E[0x6];
    unsigned char unk_94;
    char pad_95[0x3];
    unsigned char unk_98;
};

extern void func_ov002_0220a164(void *p);
extern void func_ov002_02208098(UnkStruct_0229c630 *self, int n);

void func_ov135_0229c630(UnkStruct_0229c630 *self)
{
    func_ov002_0220a164(&self->unk_98);
    self->unk_94 = self->unk_8D;
    func_ov002_02208098(self, 12);
}
