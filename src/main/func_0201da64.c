/* func_0201da64 @ 0x0201da64, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201da64 {
    char unk_00[0x830];
    void *unk_830;
};

struct UnkStruct_0201da64_2 {
    char unk_00[0x100];
    struct UnkStruct_0201da64 *sub;
    char unk_104[0x24];
    int unk_128;
    int unk_12C;
};

extern void func_0202d8f8(struct UnkStruct_0201da64_2 *a, void *b, void *c, void *d, int e);

void func_0201da64(struct UnkStruct_0201da64_2 *a, void *event)
{
    func_0202d8f8(a, &a->unk_12C, &a->unk_128, a->sub->unk_830, 0);
}
