/* func_ov055_02260c38 @ 0x02260c38, 0x30 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov055_02260a04(void *, void *);

int func_ov055_02260c38(void *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x658);
    func_ov055_02260a04((char *) self + 0x658, self);
    return 1;
}
