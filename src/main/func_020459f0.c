/* func_020459f0 @ 0x020459f0, 0x90 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Entry {
    unsigned int unk_00;
    unsigned char pad0[0xe];
    unsigned short unk_12;
    unsigned char pad1[0x8];
    unsigned char unk_1C;
    unsigned char pad2;
    signed char unk_1E;
    unsigned char pad3[5];
};
struct Input {
    unsigned int unk_00;
    unsigned int unk_04;
};
struct Pair {
    unsigned int unk_00;
    unsigned int unk_04;
};
struct Big {
    unsigned short hw;
    struct Pair pair;
};
struct Both {
    struct Big pair;
    struct Pair pair2;
};
struct TableEntry {
    unsigned char f0 : 3;
    unsigned char pad0 : 4;
    unsigned char pad1 : 1;
    unsigned char pad2 : 7;
    unsigned char f1 : 1;
    unsigned char pad3 : 2;
    signed char f2 : 4;
    unsigned char pad4 : 2;
    unsigned char pad_03[13];
};

extern struct Entry data_021c7c48[];
extern struct TableEntry data_021c7884[];
extern int func_02045d80(unsigned int *p, unsigned char arg2);
extern int func_02045a80(struct Pair *p);

int func_020459f0(int index, struct Input *p)
{
    struct Both both;
    int result;
    struct Entry *entry;
    struct TableEntry *te;
    unsigned char arg2;
    int tmp;

    both.pair.hw = 0xfff1;
    result = 0;
    entry = &data_021c7c48[index];
    both.pair.hw = entry->unk_12;
    arg2 = entry->unk_1C;
    both.pair.pair.unk_00 = p->unk_00;
    both.pair.pair.unk_04 = p->unk_04;
    tmp = func_02045d80(&both.pair.pair.unk_00, arg2);
    if (tmp < 0) {
        both.pair2.unk_00 = p->unk_00;
        both.pair2.unk_04 = p->unk_04;
        if (func_02045a80(&both.pair2) != 0) {
            result = 1;
        }
    } else {
        te = &data_021c7884[tmp];
        if (te->f0 == (unsigned char) (entry->unk_00 & 3)) {
            if (te->f2 == entry->unk_1E) {
                if (te->f1 != 0) {
                    result = 1;
                }
            }
        }
    }
    return result;
}
