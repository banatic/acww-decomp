/* func_ov104_0229d1b8 @ 0x0229d1b8, 0x34 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d1b8 {
    char pad_00[0x24a0];
    int unk_24A0;
};

extern int func_ov104_0229d3ac(struct UnkStruct_0229d1b8 *);
extern int func_ov104_0229d39c(struct UnkStruct_0229d1b8 *);
extern void func_ov002_0220a0b4(void *, int, int);
extern void func_ov002_0220a374(void *, int);

void func_ov104_0229d1b8(struct UnkStruct_0229d1b8 *self)
{
    int v1 = func_ov104_0229d3ac(self);
    int v2 = func_ov104_0229d39c(self);
    func_ov002_0220a0b4(&self->unk_24A0, v1, v2);
    func_ov002_0220a374(&self->unk_24A0, 1);
}
