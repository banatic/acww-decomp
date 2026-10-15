/* func_0201b078 @ 0x0201b078, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201b1a0(void *a);
extern int func_0201b0bc(void *a, void *b, int c, int d, int e);

struct UnkStruct_0201b078 {
    char pad_00[0x34];
    short unk_34;
    short unk_36;
    char pad1[0x1D];
    unsigned char unk_55;
};

struct UnkStruct_0201b078_2 {
    char pad_00[0x8E];
    short unk_8E;
    char pad1[0x4];
    short unk_94;
};

void func_0201b078(struct UnkStruct_0201b078 *a, struct UnkStruct_0201b078_2 *b)
{
    if (func_0201b1a0(a) == 4) {
        b->unk_94 = a->unk_34;
    } else {
        func_0201b0bc(a, &b->unk_94, a->unk_34, a->unk_36, a->unk_55);
        b->unk_8E = b->unk_94;
    }
}
