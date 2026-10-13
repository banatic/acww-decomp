/* func_020abc40 @ 0x020abc40, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020abc6c(void *p, int _x);
extern void func_020aca3c(void *p);
extern void func_0208f0c4(void *p, int x);

void func_020abc40(char *self)
{
    *(unsigned int *) (self + 0x13c) = 0;
    func_020abc6c(self, 0);
    func_020aca3c(self + 0xe4);
    self += 0x6c;
    func_0208f0c4(self, 0);
}