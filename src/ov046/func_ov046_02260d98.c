/* func_ov046_02260d98 @ 0x02260d98, 0x44 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b1580(void *p);
extern void func_020157b0(void *p, int a, int b, int c);
extern void func_02015828(void *p, int a);
extern void func_ov046_02261508(void *p, int a);

struct UnkStruct_02260d98 {
    char pad_00[0xC0];
    int unk_C0;
    char pad_C4[0x18];
    int unk_DC;
};

void func_ov046_02260d98(struct UnkStruct_02260d98 *p)
{
    p->unk_C0 = func_020b1580(p);
    if (p->unk_C0 >= 0) {
        func_020157b0(p, 46, (unsigned char) p->unk_C0, 0);
        func_02015828(p, 3);
        func_ov046_02261508(p, 1);
    } else {
        p->unk_DC = 62;
    }
}
