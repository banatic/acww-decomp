/* func_020366e0 @ 0x020366e0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02036754(int param);
extern void func_020356c4(int a, int b, int c, int d);

struct UnkStruct_020366e0 {
    char pad_00[10];
    unsigned short unk_0A;
};

void func_020366e0(struct UnkStruct_020366e0 *param1, int param2)
{
    int ret;
    int c;
    int d;

    ret = func_02036754(param2);
    c = 0x7f;
    d = 0;
    if (ret == 1) {
        c = 0x38;
    }
    if (ret == 0x14 || ret == 0x5c) {
        d = 1;
    }
    func_020356c4(0x11, ret, c, d);
    param1->unk_0A = (unsigned short) ret;
}
