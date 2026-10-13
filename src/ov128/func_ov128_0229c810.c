/* func_ov128_0229c810 @ 0x0229c810, 0x1e bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
} UnkStruct_0229c810;

extern void func_ov128_0229c408(UnkStruct_0229c810 *s);
extern void func_ov002_022080a0(UnkStruct_0229c810 *s);

int func_ov128_0229c810(UnkStruct_0229c810 *s)
{
    func_ov128_0229c408(s);
    s->unk_8C = 0;
    func_ov002_022080a0(s);
    return 1;
}
