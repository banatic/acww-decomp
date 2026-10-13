/* func_02049f74 @ 0x02049f74, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short *func_0204f5e0(int, int, int, int, int, int);
extern int func_0204ba94(unsigned short *);
extern void func_0204a198(int, unsigned short, int, int);

struct UnkStruct_02049f74 {
    int unk_00;
    int unk_04;
};

int func_02049f74(int param0, struct UnkStruct_02049f74 *param1)
{
    unsigned short *result;
    int f0, f1, hi0, hi1, low0, low1;

    f0 = param1->unk_00;
    f1 = param1->unk_04;
    hi0 = f0 >> 4;
    hi1 = f1 >> 4;
    low1 = f1 - (hi1 << 4);
    low0 = f0 - (hi0 << 4);

    result = func_0204f5e0(param0, hi0, hi1, low0, low1, 0);

    if (result != 0 && func_0204ba94(result) != 0) {
        func_0204a198(param0, *result, param1->unk_00, param1->unk_04);
    }

    return 0;
}
