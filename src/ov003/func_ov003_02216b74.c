/* func_ov003_02216b74 @ 0x02216b74, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(const char *, int);
extern void func_0200f328(char *, int);
extern void func_02010f5c(char *);

void func_ov003_02216b74(char *a)
{
    if (func_02056f28(a + 0x2d0, 6) != 0) {
        func_0200f328(a, 0x83d);
    }
    func_02010f5c(a);
}
