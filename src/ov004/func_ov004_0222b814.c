/* func_ov004_0222b814 @ 0x0222b814, 0x48 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *self);
extern int func_02056f28(void *p, int a);
extern int func_0200f328(void *self, int a);
extern int func_02073908(int a, int b);
extern void func_02051e0c(void);
extern int data_020ccf94;

void func_ov004_0222b814(char *self)
{
    func_02010f5c(self);
    if (func_02056f28(self + 0x2d0, 0x15) != 0) {
        func_0200f328(self, 0x4c6);
        if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
            func_02051e0c();
        }
    }
}
