/* func_ov102_0229e224 @ 0x0229e224, 0x28 bytes, Thumb, module ov102
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov102_0229e32c(void *);
extern void func_ov102_0229e1cc(void *);
extern void func_ov002_02208090(void *, int);

void func_ov102_0229e224(void *self)
{
    func_ov102_0229e32c(self);
    func_ov002_02208090(self, 8);
    ((unsigned char *) self)[0x25a9] = 4;
    func_ov102_0229e1cc(self);
}
