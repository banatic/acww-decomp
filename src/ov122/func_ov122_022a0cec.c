/* func_ov122_022a0cec @ 0x022a0cec, 0x98 bytes, Thumb, module ov122
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov122_0229efe8(void *self, int value);
extern int func_ov122_0229f958(void *self);
extern void func_ov122_0229f89c(void *self);
extern void func_ov095_0229b3ec(void *p);
extern void func_ov095_0229b394(void *p);
extern int func_02051c8c_unk(void *p, int n);
extern int func_ov122_022a0e90(void *self, unsigned short val, int zero);
extern void func_ov122_0229f388(void *receiver);
extern void func_ov095_022999e8(void *p);
extern void func_ov122_022a15b8(void *self, int a, int b);
extern void func_ov122_0229f9a8(void *self);
extern void func_ov095_0229b388(void *p);

void func_ov122_022a0cec(void *self)
{
    int count;
    int i;
    int zero;

    if (func_ov122_0229efe8(self, 0x400) == 0) {
        return;
    }

    if (func_ov122_0229f958(self) != 0) {
        func_ov122_0229f89c(self);
    }

    func_ov095_0229b3ec((char *) self + 0xc0);
    func_ov095_0229b394((char *) self + 0xc0);

    count = func_02051c8c_unk((char *) self + 0x4230, 0x40);
    i = 0;
    zero = 0;

    while (i < count) {
        char *p = (char *) self + i * 2;
        unsigned short val = *(unsigned short *) (p + 0x4230);
        if (func_ov122_022a0e90(self, val, zero) == 0) {
            if (i == 0) {
                func_ov122_0229f388(self);
            }
            i = count;
        }
        i++;
    }

    func_ov095_022999e8((char *) self + 0xc0);
    func_ov122_022a15b8(self, 0, 1);
    func_ov122_0229f9a8(self);
    self = (char *) self + 0xc0;
    func_ov095_0229b388(self);
}
