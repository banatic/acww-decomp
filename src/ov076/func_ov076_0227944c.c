/* func_ov076_0227944c @ 0x0227944c, 0x30 bytes, Thumb, module ov076
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(char *);
extern void func_0201c280(char *, char *);
extern void func_ov076_02278e04(char *, char *);

int func_ov076_0227944c(char *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, self + 0x658);
    func_ov076_02278e04(self + 0x658, self);
    return 1;
}
