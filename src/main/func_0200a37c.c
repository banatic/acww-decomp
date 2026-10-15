/* func_0200a37c @ 0x0200a37c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f28(void *a, int b);
extern int func_0200f328(void *a, int b);
extern void func_02010f5c(void *a);

void func_0200a37c(void *self)
{
    if (func_02056f28((char *) self + 0x2d0, 8) != 0) {
        func_0200f328(self, 0x63);
    }
    func_02010f5c(self);
}
