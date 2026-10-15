/* func_0200c200 @ 0x0200c200, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_0200c33c(void *arg);
extern int func_02073908(int a, int b);
extern void func_0200c2c8(void *arg);
extern int func_0201100c(void *arg);
extern void func_02010d64(void *arg);
extern void func_0200c258(void *arg);
extern int func_0200f554(void *arg);

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_0200c200;

void func_0200c200(void *arg)
{
    func_0200c33c(arg);
    if (func_02073908(data_020ccf94, ((UnkStruct_0200c200 *) arg)->unk_800) != 0) {
        func_0200c2c8(arg);
        func_0201100c(arg);
        func_02010d64(arg);
        func_0200c258(arg);
    } else {
        if (func_0200f554(arg) != 0) {
            func_0201100c(arg);
        }
        func_02010d64(arg);
    }
}
