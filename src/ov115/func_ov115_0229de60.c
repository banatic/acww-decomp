/* func_ov115_0229de60 @ 0x0229de60, 0x52 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov114_0229c60c(void *p);
extern int func_ov114_0229c5f4(void *p);
extern void func_ov002_0220a254(void *p);
extern void func_ov002_0220a2b4(void *p);
extern int func_ov115_0229dedc(void *p);
extern int func_ov115_0229ded0(void *p);
extern void func_ov115_0229de2c(void *p, int a, int b);

void func_ov115_0229de60(void *self)
{
    if (func_ov114_0229c60c((char *) self + 0xf8) != -1 || func_ov114_0229c5f4((char *) self + 0xf8) != 0) {
        func_ov002_0220a254((char *) self + 0x94);
    } else {
        func_ov002_0220a2b4((char *) self + 0x94);
    }
    func_ov115_0229de2c(self, func_ov115_0229dedc(self), func_ov115_0229ded0(self));
}
