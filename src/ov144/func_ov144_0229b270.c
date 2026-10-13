/* func_ov144_0229b270 @ 0x0229b270, 0x1e bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov144_0229ae24(void *);
extern void func_ov002_022080a0(void *);

typedef struct {
    char pad_00[0x8c];
    char unk_8C;
} UnkStruct_0229b270;

int func_ov144_0229b270(UnkStruct_0229b270 *self)
{
    func_ov144_0229ae24(self);
    self->unk_8C = 0;
    func_ov002_022080a0(self);
    return 1;
}
