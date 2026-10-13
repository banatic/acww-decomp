/* func_02046730 @ 0x02046730, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0204e414(void);
extern void func_0204f778(int, int, int, int, int);
typedef struct {
    char pad_00[0x34];
    int unk_34;
    int unk_38;
    int unk_3C;
    int unk_40;
} UnkStruct_02046730;
extern UnkStruct_02046730 data_021c79c4;

int func_02046730(int param)
{
    int result = 0;
    int a = data_021c79c4.unk_34;
    int b = data_021c79c4.unk_38;
    int c = data_021c79c4.unk_3C;
    int d = data_021c79c4.unk_40;
    if (a != -1 && b != -1 && c != -1 && d != -1) {
        if (func_0204e414() != 0) {
            func_0204f778(param, a + 1, b + 1, c, d);
            result = 1;
        }
    }
    return result;
}
