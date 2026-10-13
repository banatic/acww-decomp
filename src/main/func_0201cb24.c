/* func_0201cb24 @ 0x0201cb24, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct Pair {
    int a;
    int b;
} data_020d9340;

struct UnkStruct_0201cb24 {
    char pad_00[0x48];
    unsigned char unk_48;
    char pad_49[3];
    struct Pair pair;
};

int func_0201cb24(struct UnkStruct_0201cb24 *param0)
{
    param0->unk_48 = 0;
    param0->pair = data_020d9340;
    return 1;
}
