/* func_ov003_02214644 @ 0x02214644, 0x78 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02214644_2 {
    char pad_00[0xc];
    short unk_0C;
    char pad1[0x1c - 0xc - 2];
} UnkStruct_02214644_2;

typedef struct UnkStruct_02214644 {
    char pad_00[0x8e];
    short unk_8E;
    char pad1[0x144 - 0x90];
    int unk_144;
    char pad_148[0x14c - 0x148];
    int unk_14C;
    char pad_150[0x154 - 0x150];
    int unk_154;
    char pad_158[0x6f4 - 0x158];
    int unk_6F4;
    char pad_6F8[0x6fc - 0x6f8];
    int unk_6FC;
} UnkStruct_02214644;

extern void func_0200e92c(UnkStruct_02214644_2 *local);
extern void func_0200e90c(UnkStruct_02214644_2 *local, int x, int y, int z);
extern int func_020e8ed8(int a, int b);
extern int func_0200e894(UnkStruct_02214644 *s, UnkStruct_02214644_2 *local);
extern void func_0200e91c(UnkStruct_02214644_2 *local);

int func_ov003_02214644(UnkStruct_02214644 *s, int a, int b)
{
    UnkStruct_02214644_2 local;
    short *p;
    int result;

    func_0200e92c(&local);
    p = &local.unk_0C;
    func_0200e90c(&local, 0x56, a, b);

    if (s->unk_144 == 2) {
        *p = (short) func_020e8ed8(s->unk_14C - s->unk_6F4, s->unk_154 - s->unk_6FC);
    } else {
        *p = s->unk_8E;
    }

    result = func_0200e894(s, &local);
    func_0200e91c(&local);

    return result;
}
