/* func_ov085_0227918c @ 0x0227918c, 0x94 bytes, Thumb, module ov085
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *);
extern void func_ov085_022790ec(void *, int);
extern void func_02016764(void *, void *, int, int, int, int, int, int);
extern void func_02054188(void *, int, int);
extern unsigned char func_0203fdc4(int);
extern void func_020865d8(void *, int);
extern int func_0202ea80(int, int);
extern void func_02086794(void *);
extern int data_021f3aa4;

int func_ov085_0227918c(void *self)
{
    void *g;

    if (func_0202ec58(self) == 0) {
        return 0;
    }

    func_ov085_022790ec(self, 0);
    func_02016764((char *) self + 0x334, self, 0x140, 0, 0, 0x1000, 0, 1);
    func_02054188((char *) self + 0xec, 0xc, 0xe);

    *((unsigned int *) ((char *) self + 0x4e8)) |= 2;
    *((unsigned char *) ((char *) self + 0x728)) = func_0203fdc4(0x11);

    g = (void *) &data_021f3aa4;
    func_020865d8(g, 1);

    if (func_0202ea80(0x1f, 0) == 0) {
        func_02086794(g);
    }

    return 1;
}
