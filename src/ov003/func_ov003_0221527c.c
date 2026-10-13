/* func_ov003_0221527c @ 0x0221527c, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_02010f5c(void *);
extern void func_0200f554(void *);
extern void func_02010d64(void *);
extern int func_02073908(int, int);
extern void func_ov003_022152b4(void *);

struct some_struct {
    char pad_00[0x800];
    int unk_800;
};

void func_ov003_0221527c(struct some_struct *s)
{
    func_02010f5c(s);
    func_0200f554(s);
    func_02010d64(s);
    if (func_02073908(data_020ccf94, s->unk_800) != 0) {
        func_ov003_022152b4(s);
    }
}
