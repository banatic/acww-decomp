/* func_020943c0 @ 0x020943c0, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02034270(void *p, int b, int c, int d);
extern void func_0203423c(void *p);
extern int func_02094cf8(int sel, int a, int b, int c, int d, int zero);

typedef struct {
    char pad_00[0x34];
    int unk_34;
    char pad_38[0x0c];
} UnkStruct_020943c0;

int func_020943c0(int a, int b, int c, int d)
{
    UnkStruct_020943c0 local;
    int sel;
    int result;

    func_02034270(&local, b, 0, 0);
    sel = (local.unk_34 == 0x13) ? 0x30 : 0x2f;
    result = func_02094cf8(sel, a, b, c, d, 0);
    func_0203423c(&local);
    return result;
}
