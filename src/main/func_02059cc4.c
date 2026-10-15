/* func_02059cc4 @ 0x02059cc4, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct Params {
    char pad_00[0xc];
    unsigned short unk_0C;
};

struct Entry {
    char pad_00[0xc];
    char data[0xc];
};

extern struct Entry *data_020dd31c[];
extern int func_02059d28(struct Params *a);

void *func_02059cc4(struct Params *a, int index)
{
    if (a->unk_0C == 9) {
        return data_020dd31c[3][index].data;
    } else {
        return data_020dd31c[func_02059d28(a)][index].data;
    }
}
