/* star_designer_input_2: 2 functions, module ov129
 * mwccarm 1.2/base -O4,s
 * func_ov129_0229c39c @ 0x0229c39c, 0x58 bytes, Thumb
 * func_ov129_0229c368 @ 0x0229c368, 0x34 bytes, Thumb
 */

extern int func_ov129_0229c548(void *self);
extern int func_ov129_0229c520(void *self);
extern int func_ov129_0229c468(void *self);
extern int func_ov129_0229c418(void *self);
extern void func_ov002_0220a2b4(void *p);
extern void func_ov002_0220a314(void *p);
extern void func_ov002_0220a254(void *p);
extern void func_ov002_0220a05c(unsigned char *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov129_0229c368(unsigned char *base, int a, int b);

void func_ov129_0229c39c(void *self)
{
    if (func_ov129_0229c548(self)) {
        func_ov002_0220a2b4((char *) self + 0x3a0);
    } else if (func_ov129_0229c520(self)) {
        func_ov002_0220a314((char *) self + 0x3a0);
    } else {
        func_ov002_0220a254((char *) self + 0x3a0);
    }
    {
        int p = func_ov129_0229c468(self);
        int q = func_ov129_0229c418(self);
        func_ov129_0229c368((unsigned char *) self, p, q);
    }
}

void func_ov129_0229c368(unsigned char *base, int a, int b)
{
    func_ov002_0220a05c(base + 0x3a0, a, b, 3, 1);
    base[0xac] = base[0x8d];
    func_ov002_02208098((void *) (base), 7);
}
