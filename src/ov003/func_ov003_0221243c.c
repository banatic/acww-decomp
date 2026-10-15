/* func_ov003_0221243c @ 0x0221243c, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(char *p, int a);
extern int func_0200f328(char *p, int b);
extern void func_02010f5c(char *p);

void func_ov003_0221243c(char *p)
{
    if (func_02056f28(p + 0x2d0, 5)) {
        func_0200f328(p, 0x842);
    }
    func_02010f5c(p);
}
