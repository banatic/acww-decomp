/* func_0200c120 @ 0x0200c120, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020ccf94;
extern int func_02073908(unsigned int a, unsigned int b);
extern void func_02010f5c(void *p);
extern void func_0200f554(void *p);
extern void func_02010d64(void *p);
extern void func_0200c158(void *p);

typedef struct UnkStruct_0200c120 {
    char pad_00[0x800];
    unsigned int unk_800;
} UnkStruct_0200c120;

void func_0200c120(UnkStruct_0200c120 *p)
{
    func_02010f5c(p);
    if (func_02073908(data_020ccf94, p->unk_800) == 0) {
        func_0200f554(p);
    }
    func_02010d64(p);
    func_0200c158(p);
}
