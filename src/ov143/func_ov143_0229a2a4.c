/* func_ov143_0229a2a4 @ 0x0229a2a4, 0x24 bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov143_0229a134(void *);
extern void func_ov002_02207fc0(void *);
extern void func_ov002_02208098(void *, int);

void func_ov143_0229a2a4(void *self)
{
    char *p = (char *) self + 0xa4;
    *p = 0x15;
    func_ov143_0229a134(self);
    func_ov002_02207fc0(self);
    func_ov002_02208098(self, 8);
}
