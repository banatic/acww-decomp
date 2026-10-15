/* func_ov105_0229c4cc @ 0x0229c4cc, 0x90 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov094_0229b288(void *a, void *b);
extern int func_02002c6c(void *a, void *b, int c, int d, int e, int f);
extern void func_ov002_02207f20(void *a, int b, int c, int d, int e);
extern void func_ov002_02207e90(void *a, int b);
extern void func_02002708(int a);
extern void func_ov105_0229c330(void *a, int b);
extern void func_ov105_0229ed78(void *a);
extern void *data_ov105_0229f890[];
extern void *data_021fbe94;

void func_ov105_0229c4cc(void *self)
{
    func_ov094_0229b288((char *) self + 0x0d5c,
                        (char *) self + 0x2db8 + (((*(unsigned char *) ((char *) self + 0x2c0)) * 25) << 8));
    func_02002c6c(data_ov105_0229f890[*(unsigned char *) ((char *) self + 0x2c0)], data_021fbe94, 4, 0x1e2, 0x1e2, 0x1ed);
    func_ov002_02207f20(self, 2, 0, 2, 0x30);
    func_ov002_02207e90(self, 0xc0);
    func_02002708(4);
    func_ov105_0229c330(self, 0x200);
    func_ov105_0229ed78(self);
}
