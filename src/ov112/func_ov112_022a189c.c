/* func_ov112_022a189c @ 0x022a189c, 0xc4 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov112_022a11f4(void);
extern void func_ov112_022a1104(void *self);
extern void func_ov112_0229fbc0(void *self);
extern void func_ov112_0229fe60(void *self, int arg);
extern void func_ov095_0229c420(void *ptr, int a);
extern void func_ov095_0229bf7c(void *ptr, int a);
extern void func_ov002_02207f20(void *self, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov002_02207e80(void *self, int a, int b, int c);
extern void func_ov002_02208090(void *self, int a);
extern int func_ov002_02207f60(void *self);
extern int func_ov002_0220acc4(void *ptr);
extern void func_ov112_0229fd20(void *self);
extern void func_ov112_022a122c(void *self);

void func_ov112_022a189c(void *self)
{
    func_ov112_022a11f4();
    func_ov112_022a1104(self);
    func_ov112_0229fbc0(self);
    func_ov112_0229fe60(self, 0x4000);
    func_ov095_0229c420((char *) self + 0x384, 6);
    func_ov095_0229bf7c((char *) self + 0x384, 6);
    func_ov002_02207f20(self, 10, 7, 0, 0x30);
    func_02002708(4);
    func_02002708(6);
    func_ov002_02207e80(self, 4, 0, ~7);
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02208090(self, 1);
    *(unsigned int *) ((char *) self + 0xa0) = func_ov002_02207f60(self);
    *(unsigned int *) ((char *) self + 0xa4) = *(unsigned int *) ((char *) self + 0xa0);
    *(unsigned int *) ((char *) self + 0xa8) = *(unsigned int *) ((char *) self + 0xa4);
    func_ov112_0229fe60(self, 0x81);
    func_ov002_0220acc4((char *) self + 0x427c);
    func_ov112_0229fd20(self);
    func_ov112_022a122c(self);
}
