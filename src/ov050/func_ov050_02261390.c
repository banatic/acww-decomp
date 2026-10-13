/* func_ov050_02261390 @ 0x02261390, 0x48 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02261390 {
    char pad_00[0xb4];
    unsigned int unk_B4;
    char pad_B8[12];
    unsigned int unk_C4;
    char pad_C8[8];
    unsigned int unk_D0;
};

extern int func_02099fe8(void);
extern int func_0201b43c(unsigned int, unsigned int);
extern void func_ov050_02260dd4(struct UnkStruct_02261390 *);

void func_ov050_02261390(struct UnkStruct_02261390 *p, int flag)
{
    if (flag != 0) {
        return;
    }
    if (func_02099fe8() < 0) {
        p->unk_D0 = 0x20;
        return;
    }
    if (func_0201b43c(p->unk_B4, p->unk_C4) == 0) {
        p->unk_D0 = 0x21;
        return;
    }
    p->unk_D0 = 0x22;
    func_ov050_02260dd4(p);
}
