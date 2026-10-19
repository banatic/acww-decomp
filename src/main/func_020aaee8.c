/* func_020aaee8 @ 0x020aaee8, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020ab550(int a, int b);
extern int func_020ab780(int a);
extern void func_0200467c(int command);

struct UnkStruct_020aaee8 {
    int unk_00;
    unsigned char pad_04[28];
    int unk_20;
};

void func_020aaee8(struct UnkStruct_020aaee8 *arg)
{
    int result;
    int cmd;

    result = func_020ab780(func_020ab550(arg->unk_20, arg->unk_00));
    cmd = 0x29;
    if (result == 1) {
        cmd = 0x3a;
    } else if (result == 2) {
        cmd = 0x6a;
    } else if (result == 3) {
        cmd = 0x6c;
    }
    func_0200467c(cmd);
}
