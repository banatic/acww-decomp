/* func_ov085_02279220 @ 0x02279220, 0x30 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202edc8(void *);
extern void func_0201c280(void *, void *);
extern void func_ov085_02278eb8(void *, void *);

int func_ov085_02279220(void *self)
{
    if (func_0202edc8(self) == 0) {
        return 0;
    }
    func_0201c280(self, (char *) self + 0x658);
    func_ov085_02278eb8((char *) self + 0x658, self);
    return 1;
}
