/* func_ov003_022146bc @ 0x022146bc, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_02010f5c(void *);
extern int func_0200f554(void *);
extern void func_02010d64(void *);
extern int func_02073908(int, int);
extern void func_ov003_0221474c(void *);
extern void func_ov003_022146fc(void *);

struct UnkStruct_022146bc {
    char pad_00[0x800];
    int unk_800;
};

void func_ov003_022146bc(struct UnkStruct_022146bc *arg)
{
    func_02010f5c(arg);
    func_0200f554(arg);
    func_02010d64(arg);
    if (func_02073908(data_020ccf94, arg->unk_800) != 0) {
        func_ov003_0221474c(arg);
    } else {
        func_ov003_022146fc(arg);
    }
}
