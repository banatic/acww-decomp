/* func_ov146_0229aac8 @ 0x0229aac8, 0x60 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern void func_02002c6c(void *, void *, int, int, int, int);
extern void func_02002d14(void *, void *, int, int, int, int);

extern unsigned char data_ov146_0229b6e0[];
extern unsigned char data_ov146_0229b6f4[];
extern unsigned char data_ov146_0229b708[];

void func_ov146_0229aac8(void)
{
    void *obj = data_021fbe94;
    func_02002c6c((void *) data_ov146_0229b6e0, obj, 8, 0x80, 0x80, 0xff);
    func_02002c6c((void *) data_ov146_0229b6f4, obj, 8, 0x160, 0x160, 0x1ff);
    func_02002d14((void *) data_ov146_0229b708, obj, 8, 4, 4, 0xd);
}
