/* func_02094b58 @ 0x02094b58, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02091494(int, unsigned short, int, int, int, int, int);
extern int func_02090ac4(int, int, int, int);
extern void func_020914dc(int);

struct UnkStruct_02094b58 {
    unsigned char pad_00[0x1c];
    unsigned short unk_1C;
};

extern struct UnkStruct_02094b58 data_021d5658;
extern char data_020e2ac4;

int func_02094b58(int a0, int a1, int a2, int a3, int a4, int a5)
{
    int ptr = a5;
    int result;

    if (ptr == 0) {
        ptr = (int) &data_020e2ac4;
    }

    result = 3;
    func_02091494((int) &data_021d5658, data_021d5658.unk_1C, a1, a2, a3, a4, -1);

    if (func_02090ac4(a0, a2, a3, ptr) != 0) {
        result = 0;
    }

    func_020914dc((int) &data_021d5658);
    return result;
}
