/* func_ov072_0227972c @ 0x0227972c, 0x30 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov072_02278d54(void *, void *);

int func_ov072_0227972c(void *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x658);
    func_ov072_02278d54((char *) self + 0x658, self);
    return 1;
}
