/* func_ov105_0229cdbc @ 0x0229cdbc, 0x34 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229cdbc {
    char pad_00[0x24a4];
    int unk_24A4;
} UnkStruct_0229cdbc;

extern int func_ov105_0229cff4(UnkStruct_0229cdbc *self);
extern int func_ov105_0229cfe4(UnkStruct_0229cdbc *self);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int value);

void func_ov105_0229cdbc(UnkStruct_0229cdbc *self)
{
    int a;
    int b;
    a = func_ov105_0229cff4(self);
    b = func_ov105_0229cfe4(self);
    func_ov002_0220a0b4(&self->unk_24A4, a, b);
    func_ov002_0220a374(&self->unk_24A4, 1);
}
