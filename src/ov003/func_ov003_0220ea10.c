/* func_ov003_0220ea10 @ 0x0220ea10, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *ptr, int b, int c, unsigned short d);
extern int func_02073908(int a, int b);
extern void func_020ba2ec(void);
extern int data_020ccf94;

struct UnkStruct_0220ea10 {
    char pad_00[0x800];
    int unk_800;
};

void func_ov003_0220ea10(struct UnkStruct_0220ea10 *p, void *message, int previous)
{
    func_020109a0(p, 0x9C, 3, 0);
    if (func_02073908(data_020ccf94, p->unk_800)) {
        func_020ba2ec();
    }
}
