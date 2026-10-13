/* func_ov138_0229d0dc @ 0x0229d0dc, 0x5a bytes, Thumb, module ov138
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov138_0229cf3c(void *self);
extern void func_ov138_0229cf1c(void *self);
extern void func_ov138_0229cefc(void *self);
extern void func_02002708(int arg);
extern void func_ov138_0229d02c(void *self);
extern void func_ov138_0229c564(void *self, int arg);
extern void func_ov002_02207f20(void *self, int a, int b, int c, int d);
extern void func_ov002_0220ab38(void *self, int arg);
extern void func_ov002_02208090(void *self, int arg);

void func_ov138_0229d0dc(void *self)
{
    func_ov138_0229cf3c(self);
    func_ov138_0229cf1c(self);
    func_ov138_0229cefc(self);
    func_ov002_02207f20(self, 0xa, 4, 0, 0x30);
    func_02002708(6);
    func_02002708(4);
    func_ov138_0229d02c(self);
    func_ov138_0229c564(self, 1);
    func_ov002_0220ab38((char *) self + 0xfc, 0x65);
    func_ov002_02208090(self, 1);
}
