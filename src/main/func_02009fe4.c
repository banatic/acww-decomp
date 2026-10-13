/* func_02009fe4 @ 0x02009fe4, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_0200a0c8(void *p);
extern void func_0200a088(void *p);
extern int func_02073908(int a, int b);
extern void func_0201100c(void *p);
extern void func_02010ff4(void *p);
extern void func_02010d64(void *p);
extern void func_0200a02c(void *p);

struct UnkStruct_02009fe4 {
    char pad_00[0x800];
    int unk_800;
};

void func_02009fe4(struct UnkStruct_02009fe4 *param)
{
    func_0200a0c8(param);
    func_0200a088(param);
    if (func_02073908(data_020ccf94, param->unk_800) != 0) {
        func_0201100c(param);
    } else {
        func_02010ff4(param);
    }
    func_02010d64(param);
    func_0200a02c(param);
}
