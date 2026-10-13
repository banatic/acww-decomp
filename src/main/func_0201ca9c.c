/* func_0201ca9c @ 0x0201ca9c, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Pair {
    int a;
    int b;
} data_020d92d0;

struct Dest {
    unsigned char pad_00[0x48];
    unsigned char flag;
    unsigned char pad_49[3];
    struct Pair pair;
};

int func_0201ca9c(struct Dest *s)
{
    s->flag = 0;
    s->pair = data_020d92d0;
    return 1;
}
