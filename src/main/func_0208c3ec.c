/* func_0208c3ec @ 0x0208c3ec, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern const struct Pair {
    signed char lo;
    signed char hi;
} data_020d0a84[9];

struct UnkStruct_0208c3ec {
    char pad_00[0xC4];
    int unk_C4;
    int unk_C8;
    int unk_CC;
};

void func_0208c3ec(struct UnkStruct_0208c3ec *s)
{
    int i;
    for (i = 0; i < 9; i++) {
        if (s->unk_C8 == data_020d0a84[i].lo && s->unk_CC == data_020d0a84[i].hi) {
            break;
        }
    }
    s->unk_C4 = i;
}
