/* func_ov108_0229d39c @ 0x0229d39c, 0x7c bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void func_ov108_0229c468(void *self);
extern int func_ov002_02208008(void *self);
extern int func_ov002_02209044(void *a, int b, void *c, int d);
extern void func_ov108_0229c6d8(void *self);
extern void func_ov002_0220a1dc(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov108_0229c674(void *self);
extern char data_021fbe40[];

void func_ov108_0229d39c(void *self)
{
    int tmp;
    unsigned short flags;

    if (func_ov002_02208014(self)) {
        func_ov108_0229c468(self);
        return;
    }

    tmp = func_ov002_02208008(self);
    if (func_ov002_02209044((char *) self + 0x24fc, tmp, (char *) self + 0x2b5, 0)) {
        func_ov108_0229c6d8(self);
        return;
    }

    flags = *(unsigned short *) (data_021fbe40 + 2);
    if (flags & 1) {
        func_ov002_0220a1dc((char *) self + 0x2498);
        func_ov002_02208098((void *) (self), 9);
        return;
    } else if (flags & 2) {
        func_ov108_0229c674(self);
    }
}
