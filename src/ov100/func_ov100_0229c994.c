/* func_ov100_0229c994 @ 0x0229c994, 0x4c bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(void *ptr, int val);
extern void func_ov002_0220a374(void *ptr, int val);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

struct UnkStruct_0229c994 {
    unsigned char pad_00[0x8d];
    unsigned char unk_8D;
    unsigned char pad_8E[0x20FE];
    unsigned char unk_218C;
    unsigned char pad_218D[0xE7];
    unsigned char unk_2274;
    unsigned char pad_2275[0x6AE];
    unsigned char unk_2923;
    unsigned char unk_2924;
};

void func_ov100_0229c994(struct UnkStruct_0229c994 *a, unsigned char c)
{
    func_ov002_02207d24(&a->unk_218C, 1);
    a->unk_2924 = a->unk_8D;
    a->unk_2923 = c;
    func_ov002_0220a374(&a->unk_2274, 6);
    func_ov002_02208098((void *) (a), 14);
}
