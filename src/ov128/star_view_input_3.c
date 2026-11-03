/* star_view_input_3: 2 functions, module ov128
 * mwccarm 1.2/base -O4,s
 * func_ov128_0229bc88 @ 0x0229bc88, 0x5c bytes, Thumb
 * func_ov128_0229bc50 @ 0x0229bc50, 0x38 bytes, Thumb
 */

extern int func_ov128_0229b7ec(char *self, int);
extern void func_ov002_0220a2b4(char *);
extern void func_ov002_0220a254(char *);
extern int func_ov128_0229bd38(char *self);
extern int func_ov128_0229bd08(char *self);
extern void func_ov002_0220a05c(unsigned char *p, int a, int b, int c, int d);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov128_0229bc50(unsigned char *base, int a, int b);

void func_ov128_0229bc88(char *self)
{
    int a, b;
    if (func_ov128_0229b7ec(self, 2)) {
        func_ov002_0220a2b4(self + 0x110);
    } else {
        if (*(unsigned char *) (self + 0x2d6c) == 3) {
            func_ov002_0220a254(self + 0x110);
        } else {
            func_ov002_0220a2b4(self + 0x110);
        }
    }
    a = func_ov128_0229bd38(self);
    b = func_ov128_0229bd08(self);
    func_ov128_0229bc50((unsigned char *) self, a, b);
}

void func_ov128_0229bc50(unsigned char *base, int a, int b)
{
    func_ov002_0220a05c(base + 0x110, a, b, 3, 1);
    base[0x2d6a] = base[0x8d];
    func_ov002_02208098((void *) (base), 7);
}
