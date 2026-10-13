/* func_020927c4 @ 0x020927c4, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x34];
    int unk_34;
    char pad_38[0xc];
} UnkStruct_020927c4;

extern void func_02034270(void *ptr, int a, int b, int c);
extern int func_020b6598(int x);
extern int func_02094cf8(int x, void *a, int b, int c, int d, void *e);
extern void func_0203423c(void *ptr);
extern char data_020e27a8;

int func_020927c4(void *a, int b, int c, int d)
{
    UnkStruct_020927c4 local;
    int kind;
    int msg;

    func_02034270(&local, b, 0, 0);
    kind = local.unk_34;
    msg = -1;
    if (func_020b6598(0) != 0 && kind == 3) {
        msg = 0x88;
    } else if (kind == 0x13) {
        msg = 0x87;
    }
    if (msg != -1) {
        msg = func_02094cf8(msg, a, b, c, d, &data_020e27a8);
        func_0203423c(&local);
        return msg;
    }
    func_0203423c(&local);
    return 3;
}
