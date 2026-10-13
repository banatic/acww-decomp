/* func_ov087_0227914c @ 0x0227914c, 0x70 bytes, Thumb, module ov087
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *p);
extern void func_ov087_022790ac(void *p, int a);
extern void func_02016764(void *a, void *b, int c, int d, int e, int f, int g, int h);
extern void func_02054188(void *p, int a, int b);
extern void func_020865d8(void *p, int n);

extern unsigned char data_021f3aa4[];

int func_ov087_0227914c(void *self)
{
    if (func_0202ec58(self) == 0) {
        return 0;
    }
    func_ov087_022790ac(self, 0);
    func_02016764((void *) ((char *) self + 0x334), self, 0x140, 0, 0, 0x1000, 0, 1);
    func_02054188((void *) ((char *) self + 0xec), 0xc, 0xe);
    *(unsigned int *) ((char *) self + 0x4e8) |= 2;
    func_020865d8((void *) data_021f3aa4, 2);
    return 1;
}
