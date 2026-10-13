/* func_ov004_0222bc28 @ 0x0222bc28, 0x38 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern void func_0200f554(void *);
extern void func_02010f5c(void *);
extern void func_02010ca4(void *);
extern int func_02073908(int, int);
extern void func_ov004_0222bc60(void *);

struct some_struct {
    char pad_00[0x800];
    int unk_800;
};

void func_ov004_0222bc28(struct some_struct *s)
{
    func_0200f554(s);
    func_02010f5c(s);
    func_02010ca4(s);
    if (func_02073908(data_020ccf94, s->unk_800) != 0) {
        func_ov004_0222bc60(s);
    }
}
