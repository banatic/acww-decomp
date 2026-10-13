/* func_ov068_02271f50 @ 0x02271f50, 0x2c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02271f50 {
    unsigned char pad_00[0x5c];
    int a;
    unsigned char pad_60[4];
    int b;
    unsigned char pad_68[0x26];
    short s;
};

void func_ov068_02271f50(struct UnkStruct_02271f50 *p)
{
    p->a += 0x1c00;
    p->b -= 0x2c00;
    p->s += 0x8000;
}
