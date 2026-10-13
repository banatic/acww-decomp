/* func_ov003_0221038c @ 0x0221038c, 0x40 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02210504(char *p);
extern void func_02010d64(char *p);
extern void func_02010ca4(char *p);
extern void func_ov003_02210474(char *p);
extern void func_ov003_022103cc(char *p);
extern int func_02073908(int a, int b);

extern int data_020ccf94;

void func_ov003_0221038c(char *p)
{
    func_ov003_02210504(p);
    func_02010d64(p);
    func_02010ca4(p);
    if (func_02073908(data_020ccf94, *(int *) (p + 0x800)) != 0) {
        func_ov003_02210474(p);
    } else {
        func_ov003_022103cc(p);
    }
}
