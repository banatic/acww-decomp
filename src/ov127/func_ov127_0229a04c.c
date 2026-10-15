/* func_ov127_0229a04c @ 0x0229a04c, 0x70 bytes, Thumb, module ov127
 * mwccarm 1.2/base -O4,s
 */

extern void func_020028bc(int a, int b, int c, int d);
extern void *data_ov127_0229b6ac;
extern int data_021fbe94;
extern int func_02002c6c(void *table, int deref, int b, int c, int d, int e);
extern void *data_ov127_0229b6c0;
extern int func_02064af4(void *table, void *dst, int size);
extern void func_020b0fa0(void *p);
extern int func_02002b40(void *p, int a, int b, int c);

void func_ov127_0229a04c(unsigned char *self, unsigned char param1)
{
    self[0x2832] = param1;
    func_020028bc(self[0x2832], 1, 0, 0);
    func_02002c6c(&data_ov127_0229b6ac, data_021fbe94, self[0x2832], 0x10, 0x10, 0x1f);
    func_02064af4(&data_ov127_0229b6c0, self + 0x24, 0x1000);
    func_020b0fa0(self + 0x24);
    func_02002b40(self + 0x24, self[0x2832], 0x1000, 0);
}
