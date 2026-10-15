/* func_ov003_02216970 @ 0x02216970, 0x34 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_02216970;

extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern int func_0200f290(UnkStruct_02216970 *p, int a);
extern void func_ov003_02216780(UnkStruct_02216970 *p);

void func_ov003_02216970(UnkStruct_02216970 *param)
{
    int ret;
    ret = func_02073908(data_020ccf94, param->unk_800);
    if (ret != 0) {
        return;
    }
    ret = func_0200f290(param, 0x1C);
    if (ret == 0) {
        return;
    }
    func_ov003_02216780(param);
}
