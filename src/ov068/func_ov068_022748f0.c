/* func_ov068_022748f0 @ 0x022748f0, 0x3c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022748f0 {
    char pad_00[0x730];
    int unk_730;
};

extern int func_ov068_022739f4(struct UnkStruct_022748f0 *p);
extern void func_020ee470(struct UnkStruct_022748f0 *p);
extern void func_ov004_0222daf0(void);
extern void func_ov004_0222dad8(void);

int func_ov068_022748f0(struct UnkStruct_022748f0 *p)
{
    int field = p->unk_730;
    if (field == 8) {
        func_020ee470(p);
        return 1;
    } else if (field == 7) {
        func_ov068_022739f4(p);
    } else {
        func_ov004_0222daf0();
    }
    if (p->unk_730 == 6) {
        func_ov004_0222dad8();
    }
    return 1;
}
