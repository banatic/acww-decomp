/* func_ov003_022172c4 @ 0x022172c4, 0x48 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_ov003_02217378(void *);
extern int func_02073908(int, int);
extern int func_0201100c(void *);
extern int func_0200f554(void *);
extern void func_02010d64(void *);
extern int func_02010ca4(void *);
extern void func_ov003_0221730c(void *);

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_022172c4;

void func_ov003_022172c4(void *arg)
{
    int result;
    func_ov003_02217378(arg);
    result = func_02073908(data_020ccf94, ((UnkStruct_022172c4 *) arg)->unk_800);
    if (result != 0) {
        func_0201100c(arg);
    } else {
        func_0200f554(arg);
    }
    func_02010d64(arg);
    func_02010ca4(arg);
    func_ov003_0221730c(arg);
}
