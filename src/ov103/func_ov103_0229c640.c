/* func_ov103_0229c640 @ 0x0229c640, 0x20 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_0220a374(void *, int);
extern void func_ov002_02208098(void *, int);

struct UnkStruct_0229c640 {
    char pad_00[0x2274];
    int unk_2274;
};

void func_ov103_0229c640(struct UnkStruct_0229c640 *self)
{
    func_ov002_0220a374(&self->unk_2274, 4);
    func_ov002_02208098(self, 0xe);
}
