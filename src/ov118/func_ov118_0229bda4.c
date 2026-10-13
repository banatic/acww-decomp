/* func_ov118_0229bda4 @ 0x0229bda4, 0x60 bytes, Thumb, module ov118
 * mwccarm 1.2/base -O4,s
 */

extern void func_02002d14(void *addr, void *ptr, int n, int a, int b, int c);
extern void func_02002c6c(void *addr, void *ptr, int n, int a, int b, int c);
extern void *data_021fbe94;

extern unsigned char data_ov118_0229cc68[];
extern unsigned char data_ov118_0229cc80[];
extern unsigned char data_ov118_0229cc9c[];

void func_ov118_0229bda4(void)
{
    void *ptr = data_021fbe94;
    func_02002d14((void *) data_ov118_0229cc68, ptr, 8, 6, 6, 0xe);
    func_02002c6c((void *) data_ov118_0229cc80, ptr, 8, 0xc0, 0xc0, 0xff);
    func_02002c6c((void *) data_ov118_0229cc9c, ptr, 8, 0x180, 0x180, 0x1ff);
}
