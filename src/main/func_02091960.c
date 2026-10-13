/* func_02091960 @ 0x02091960, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02091494(void *, unsigned short, int, int, int, int, int);
extern int func_02090ac4(int, int, int, void *);
extern void func_020914dc(void *);

struct UnkStruct_02091960 {
    unsigned char pad_00[0x1c];
    unsigned short unk_1C;
};

extern struct UnkStruct_02091960 data_021d5658;
extern int data_020e2ac4;

int func_02091960(int a0, int a1, int a2, int a3)
{
    struct UnkStruct_02091960 *p = &data_021d5658;
    struct UnkStruct_02091960 *q = &data_021d5658;
    int result = 3;

    func_02091494(p, q->unk_1C, a0, a1, a2, a3, 0xf);
    if (func_02090ac4(0xf, a1, a2, &data_020e2ac4) != 0) {
        result = 2;
    }
    func_020914dc(p);

    return result;
}
