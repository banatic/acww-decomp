/* func_ov115_0229dfc0 @ 0x0229dfc0, 0x50 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov114_0229d1dc(void *);
extern void func_ov002_02208098(void *, int);
extern void func_ov115_0229ddd0(void *);
extern void func_ov114_0229d52c(void *, int);
extern int func_ov115_0229dedc(void *);
extern int func_ov115_0229ded0(void *);
extern void func_ov002_0220a0b4(void *, int, int);

void func_ov115_0229dfc0(void *self)
{
    if (func_ov114_0229d1dc((char *) self + 0xf8)) {
        func_ov002_02208098(self, 2);
        func_ov115_0229ddd0(self);
    }
    func_ov114_0229d52c((char *) self + 0xf8, *(int *) ((char *) self + 0x1424));
    func_ov002_0220a0b4((char *) self + 0x94, func_ov115_0229dedc(self), func_ov115_0229ded0(self));
}
