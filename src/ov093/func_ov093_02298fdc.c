/* func_ov093_02298fdc @ 0x02298fdc, 0x6c bytes, Thumb, module ov093
 * mwccarm 1.2/base -O4,s
 */

extern int func_02002ca4(int a, int b, int c);
extern int func_02002c6c(int a, int b, int c, int d, int e, int f);

extern int data_021fbe94;
extern int data_ov093_02299884;

extern unsigned char data_ov093_022998c8[];
extern unsigned char data_ov093_022998dc[];
extern unsigned char data_ov093_022998f4[];

void func_ov093_02298fdc(void *self)
{
    int r4 = data_021fbe94;
    func_02002ca4((unsigned int) data_ov093_022998c8, r4, 0);
    func_02002c6c(data_ov093_02299884, r4, 0, 0x10, 0x10, 0x78);
    func_02002c6c((unsigned int) data_ov093_022998dc, r4, 0, 0x79, 0x79, 0xf0);
    func_02002c6c((unsigned int) data_ov093_022998f4, r4, 0, 0xf1, 0xf1, 0x15f);
}
