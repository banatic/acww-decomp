/* fish_catalog_2: 2 functions, module ov115
 * mwccarm 1.2/base -O4,s
 * func_ov115_0229de60 @ 0x0229de60, 0x52 bytes, Thumb
 * func_ov115_0229de2c @ 0x0229de2c, 0x34 bytes, Thumb
 */

extern int func_ov114_0229c60c(void *p);
extern int func_ov114_0229c5f4(void *p);
extern void func_ov002_0220a254(void *p);
extern void func_ov002_0220a2b4(void *p);
extern int func_ov115_0229dedc(void *p);
extern int func_ov115_0229ded0(void *p);
extern void func_ov002_0220a05c(unsigned char *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov115_0229de2c(unsigned char *obj, int arg1, int arg2);

void func_ov115_0229de60(void *self)
{
    if (func_ov114_0229c60c((char *) self + 0xf8) != -1 || func_ov114_0229c5f4((char *) self + 0xf8) != 0) {
        func_ov002_0220a254((char *) self + 0x94);
    } else {
        func_ov002_0220a2b4((char *) self + 0x94);
    }
    func_ov115_0229de2c((unsigned char *) self, func_ov115_0229dedc(self), func_ov115_0229ded0(self));
}

void func_ov115_0229de2c(unsigned char *obj, int arg1, int arg2)
{
    func_ov002_0220a05c(&obj[0x94], arg1, arg2, 3, 1);
    obj[0x142c] = obj[0x8d];
    func_ov002_02208098((void *) (obj), 3);
}
