/* func_ov146_0229ab28 @ 0x0229ab28, 0xb8 bytes, Thumb, module ov146
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern unsigned char data_ov146_0229b71c[];
extern unsigned char data_ov146_0229b72c[];
extern unsigned char data_ov146_0229b73c[];
extern unsigned char data_ov146_0229b750[];
extern unsigned char data_ov146_0229b764[];
extern void func_02002c6c(void *, void *, int, int, int, int);
extern void func_02002d14(void *, void *, int, int, int, int);
extern void func_02064af4(void *, void *, int);
extern void MIi_CpuCopy16(void *, void *, int);
extern void func_02002ca4(void *, void *, int);
extern void func_0206fdd4(void *, int, int, int, int, int);

void func_ov146_0229ab28(unsigned char *base)
{
    void *p = data_021fbe94;
    func_02002c6c(data_ov146_0229b71c, p, 6, 0x11, 0x11, 0x5c);
    func_02002d14(data_ov146_0229b72c, p, 6, 1, 1, 8);
    func_02064af4(data_ov146_0229b73c, base + 0x158a, 0x20);
    MIi_CpuCopy16(base + 0x158a, base + 0x15aa, 0x20);
    func_02002ca4(data_ov146_0229b750, p, 6);
    func_02064af4(data_ov146_0229b764, base + 0x58a, 0x800);
    func_0206fdd4(base + 0x58a, 5, 7, 0xe, 0x14, 7);
    func_0206fdd4(base + 0x58a, 0x10, 7, 0x17, 0x14, 7);
}
