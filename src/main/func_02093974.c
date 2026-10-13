/* func_02093974 @ 0x02093974, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094c38(void *, int, int);

struct UnkStructB {
    unsigned char pad_00[0x54];
    unsigned int unk_54;
};

struct UnkStructA {
    unsigned char pad_00[0xC];
    struct UnkStructB *unk_0C;
};

void func_02093974(struct UnkStructA *a)
{
    struct UnkStructB *b;
    unsigned int val;
    func_02094c38(a, 0, 0);
    val = 0x4CD;
    b = a->unk_0C;
    b->unk_54 = val;
}
