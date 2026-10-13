/* func_0200aaa0 @ 0x0200aaa0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_0200aaa0;
extern int func_02073908(int, int);
extern int func_0200f290(UnkStruct_0200aaa0 *, int);
extern void func_0200a764(UnkStruct_0200aaa0 *);

void func_0200aaa0(UnkStruct_0200aaa0 *param)
{
    if (func_02073908(data_020ccf94, param->unk_800) != 0) {
        return;
    }
    if (func_0200f290(param, 0x1c) == 0) {
        return;
    }
    func_0200a764(param);
}
