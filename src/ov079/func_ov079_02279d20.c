/* func_ov079_02279d20 @ 0x02279d20, 0x30 bytes, Thumb, module ov079
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov079_02278c7c(void *, void *);

int func_ov079_02279d20(void *self)
{
    if (!func_0202edc8(self)) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x658);
    func_ov079_02278c7c((char *) self + 0x658, self);
    return 1;
}
