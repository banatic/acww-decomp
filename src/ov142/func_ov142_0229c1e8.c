/* func_ov142_0229c1e8 @ 0x0229c1e8, 0x1e bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8c];
    unsigned char unk_8C;
} UnkStruct_0229c1e8;

extern void func_ov142_0229ba64(UnkStruct_0229c1e8 *);
extern void func_ov002_022080a0(UnkStruct_0229c1e8 *);

int func_ov142_0229c1e8(UnkStruct_0229c1e8 *self)
{
    func_ov142_0229ba64(self);
    self->unk_8C = 0;
    func_ov002_022080a0(self);
    return 1;
}
