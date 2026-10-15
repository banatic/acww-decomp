/* func_ov096_022a1744 @ 0x022a1744, 0x50 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207d24(void *ptr, int val);
extern void func_ov096_0229ddd8(void *self);
extern void func_ov002_02207f04(void *self, int a, int b, int c, int d);
extern void func_ov002_02207e80(void *self, int a, int b, int c);
extern void func_ov002_02208090(void *self, int a);
extern int func_ov002_02207f60(void *self);

void func_ov096_022a1744(void *self)
{
    func_ov002_02207d24((char *) self + 0x2418, 1);
    func_ov096_0229ddd8(self);
    func_ov002_02207f04(self, 8, 0, 0, 0x30);
    func_ov002_02207e80(self, 6, 0, 0);
    func_ov002_02208090(self, 6);
    *(int *) ((char *) self + 0x98) = func_ov002_02207f60(self);
}
