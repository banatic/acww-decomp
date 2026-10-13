/* func_ov108_0229ce68 @ 0x0229ce68, 0x4c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *p, int n);
extern void func_ov108_0229c8c8(void *p, int n);
extern void func_ov108_0229c940(void *p);

struct UnkStruct_0229ce68 {
    char pad_00[0x2ac];
    unsigned char unk_2AC;
    char pad_2AD[2];
    unsigned char unk_2AF;
    char pad_2B0[3];
    unsigned char unk_2B3;
    char pad_2B4[0x20fc];
    unsigned char unk_23B0;
};

void func_ov108_0229ce68(struct UnkStruct_0229ce68 *s, int value)
{
    s->unk_2AF = value;
    func_ov002_02207d24(&s->unk_23B0, 1);
    func_ov108_0229c8c8(s, value);
    if (s->unk_2AC == 1) {
        s->unk_2B3 = 7;
    }
    func_ov108_0229c940(s);
}
