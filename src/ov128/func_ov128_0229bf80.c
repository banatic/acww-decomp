/* func_ov128_0229bf80 @ 0x0229bf80, 0x70 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void func_ov128_0229be44(void *p);
extern void func_ov128_0229bdd4(void *p);
extern int func_ov128_0229bae0(void *receiver);
extern void func_ov128_0229bb20(void *p);
extern void func_ov127_02299c08(void *p, int state, int flag);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern unsigned short data_021fbe40[2];

void func_ov128_0229bf80(void *this)
{
    unsigned char *self = (unsigned char *) this;
    unsigned short flags;
    int ret;

    if (func_ov002_02208014(this)) {
        func_ov128_0229be44(this);
        return;
    }
    flags = data_021fbe40[1];
    if ((flags & 2) != 0 || (flags & 8) != 0) {
        func_ov128_0229bdd4(this);
        return;
    }
    ret = func_ov128_0229bae0(this);
    self[0x2d6b] = (unsigned char) ret;
    if (self[0x2d6b] == 4) {
        return;
    }
    func_ov127_02299c08(self + 0x4a4, self[0x2d6b], 1);
    func_ov128_0229bb20(this);
    func_ov002_02208098((void *) (this), 5);
}
