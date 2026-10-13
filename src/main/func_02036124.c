/* func_02036124 @ 0x02036124, 0x62 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b65c4(int param0);
extern void func_02036558(void *param1, int param2, int param3, int param4);

typedef struct {
    char pad_00[0xc];
    int unk_0C;
} UnkStruct_02036124;

void func_02036124(int param0, UnkStruct_02036124 *param1)
{
    int field = param1->unk_0C;
    int ret = func_020b65c4(param0);
    int flag27 = (ret == 0x27);
    int flag28 = (ret == 0x28);

    if (field == 0) {
        if (flag27 || flag28) {
            func_02036558(param1, 0x40, 0x28, 1);
            param1->unk_0C = 0x11;
        }
    } else if (field == 0x11) {
        if (!flag27 && !flag28) {
            func_02036558(param1, 0x7f, 0x28, 1);
            param1->unk_0C = 0;
        }
    }
}
