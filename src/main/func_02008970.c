/* func_02008970 @ 0x02008970, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_020089dc(void *arg);
extern int func_02073908(int a, int b);
extern void func_02010d64(void *arg);
extern void func_020089b0(void *arg);
extern int func_0200f554(void *arg);

typedef struct {
    char pad_00[0x800];
    int unk_800;
} UnkStruct_02008970;

void func_02008970(UnkStruct_02008970 *arg)
{
    func_020089dc(arg);
    if (func_02073908(data_020ccf94, arg->unk_800) != 0) {
        func_02010d64(arg);
        func_020089b0(arg);
    } else {
        func_0200f554(arg);
        func_02010d64(arg);
    }
}
