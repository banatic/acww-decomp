/* func_0201c280 @ 0x0201c280, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201c280 {
    char pad_00[0x634];
    int unk_634;
};

extern void func_020160d0(int, struct UnkStruct_0201c280 *);

void func_0201c280(struct UnkStruct_0201c280 *s, int value)
{
    s->unk_634 = value;
    if (s->unk_634 != 0) {
        func_020160d0(s->unk_634, s);
    }
}
