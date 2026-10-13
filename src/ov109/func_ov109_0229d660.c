/* func_ov109_0229d660 @ 0x0229d660, 0x40 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229d660 {
    unsigned char pad_00[0x29b8];
    unsigned int unk_29B8;
} UnkStruct_0229d660;

extern int func_ov002_02207f48(UnkStruct_0229d660 *self, int a);
extern void func_ov002_022080a0(UnkStruct_0229d660 *self, int a);
extern void func_ov109_0229cd9c(UnkStruct_0229d660 *self);
extern void func_ov002_02207e80(UnkStruct_0229d660 *self, int a, int b, int c);
extern unsigned int func_ov002_02207f60(UnkStruct_0229d660 *self);

void func_ov109_0229d660(UnkStruct_0229d660 *self)
{
    if (func_ov002_02207f48(self, 0)) {
        func_ov002_022080a0(self, 2);
        func_ov109_0229cd9c(self);
    }
    func_ov002_02207e80(self, 6, 0, ~0xf);
    self->unk_29B8 = func_ov002_02207f60(self);
}
