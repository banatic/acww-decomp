/* func_ov107_0229c3c4 @ 0x0229c3c4, 0x4e bytes, Thumb, module ov107
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c3c4;

extern int func_020436a8(int);
extern void func_020431b8(int);
extern void func_ov002_02208098(struct UnkStruct_0229c3c4 *, int);
extern void func_ov107_0229c378(struct UnkStruct_0229c3c4 *);
extern void func_ov107_0229d480(struct UnkStruct_0229c3c4 *);
extern void func_ov107_0229d3a0(struct UnkStruct_0229c3c4 *, int, int);

struct UnkStruct_0229c3c4 {
    char pad_00[0xac];
    int unk_AC;
};

void func_ov107_0229c3c4(struct UnkStruct_0229c3c4 *self)
{
    int v = func_020436a8(self->unk_AC);
    if (v == 1) {
        goto case1;
    }
    if (v == 2) {
        goto case2;
    }
    return;
case1:
    func_ov002_02208098(self, 0x17);
    func_ov107_0229c378(self);
    goto common;
case2:
    func_ov107_0229d480(self);
    func_ov107_0229d3a0(self, 3, 0xff);
common:
    func_020431b8(self->unk_AC);
    self->unk_AC = -1;
}
