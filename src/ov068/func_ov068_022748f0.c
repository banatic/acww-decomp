/* func_ov068_022748f0 @ 0x022748f0, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022748f0 {
    char pad_00[0x730];
    int unk_730;
};

extern void func_ov068_022739f4(struct UnkStruct_022748f0 *p, int field);
extern void func_020ee470(struct UnkStruct_022748f0 *p, int field);
extern void func_ov004_0222daf0(struct UnkStruct_022748f0 *p, int field);
extern void func_ov004_0222dad8(int field);

int func_ov068_022748f0(struct UnkStruct_022748f0 *p)
{
    int field = p->unk_730;
    if (field == 8) {
        func_020ee470(p, field);
        return 1;
    } else if (field == 7) {
        func_ov068_022739f4(p, field);
    } else {
        func_ov004_0222daf0(p, field);
    }
    if (p->unk_730 == 6) {
        func_ov004_0222dad8(p->unk_730);
    }
    return 1;
}
