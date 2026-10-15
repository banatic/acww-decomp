/* func_ov138_0229cba4 @ 0x0229cba4, 0x48 bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov134_02299a60(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov138_0229c630(void *);
extern int func_ov138_0229c7a8(void *);
extern int func_ov138_0229c754(void *);
extern void func_ov002_0220a0b4(void *, int, int);

void func_ov138_0229cba4(void *self)
{
    int a;
    int b;
    if (func_ov134_02299a60((char *) self + 0x2c8)) {
        func_ov002_02208098((void *) (self), 5);
        func_ov138_0229c630(self);
    }
    a = func_ov138_0229c7a8(self);
    b = func_ov138_0229c754(self);
    self = (char *) self + 0x98;
    func_ov002_0220a0b4(self, a, b);
}
