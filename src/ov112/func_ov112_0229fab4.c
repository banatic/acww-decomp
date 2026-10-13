/* func_ov112_0229fab4 @ 0x0229fab4, 0x34 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229fab4;
extern void func_ov112_0229fb7c(struct UnkStruct_0229fab4 *p, int value);

struct UnkStruct_0229fab4 {
    char pad_00[0x9C];
    int unk_9C;
    char pad_A0[0xB7 - 0xA0];
    unsigned char unk_B7;
};

void func_ov112_0229fab4(struct UnkStruct_0229fab4 *p)
{
    unsigned char b = p->unk_B7;
    int w = p->unk_9C;
    int diff = w - b;
    if (diff < 0x18) {
        func_ov112_0229fb7c(p, b - (0x18 - diff));
    } else if (diff > 0x40) {
        func_ov112_0229fb7c(p, b + (diff - 0x38));
    }
}
