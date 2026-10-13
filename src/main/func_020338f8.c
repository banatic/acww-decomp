/* func_020338f8 @ 0x020338f8, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020338f8 {
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0C;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1C;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2C;
};

extern void func_02034280(int *, int *);
extern void func_0202f6ac(struct UnkStruct_020338f8 *, int *, int *, int *);

int func_020338f8(struct UnkStruct_020338f8 *a, struct UnkStruct_020338f8 *b)
{
    func_02034280(&a->unk_20, &b->unk_20);
    func_0202f6ac(a, &b->unk_04, &b->unk_0C, &b->unk_14);
    a->unk_28 = b->unk_28;
    a->unk_2C = b->unk_2C;
    return 1;
}
