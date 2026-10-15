/* func_ov144_0229a7e8 @ 0x0229a7e8, 0x3a bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov144_02299680(void *p, int n);
extern void func_ov144_02299660(void *p, int n);
extern void func_ov144_0229a264(void *p);
extern void func_ov002_02207fc0(void *p);
extern unsigned char *func_ov002_02208098(void *p, unsigned char n);

unsigned char *func_ov144_0229a7e8(void *self)
{
    if (func_ov144_02299680(self, 0x10)) {
        func_ov144_02299660(self, 0x10);
    } else {
        *((char *) self + 0xc1) = 0xb;
    }
    func_ov144_0229a264(self);
    func_ov002_02207fc0(self);
    return func_ov002_02208098(self, 3);
}
