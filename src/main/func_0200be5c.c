/* func_0200be5c @ 0x0200be5c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *);
extern int func_02056f28(void *, int);
extern void func_020912d4(int, void *, int, int);
extern void func_0200f328(void *, int);

void func_0200be5c(void *self)
{
    int zero = 0;
    func_02010f5c(self);
    if (func_02056f28((char *) self + 0x2d0, 6)) {
        func_020912d4(0x50, (char *) self + 0x6e0, zero, zero);
        func_0200f328(self, 0x68);
    }
}
