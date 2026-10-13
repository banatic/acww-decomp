/* func_ov147_02299248 @ 0x02299248, 0xd8 bytes, Thumb, module ov147
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203de6c(int);
extern void func_020028bc(int, int, int, int);
extern void func_020029e8(int, int);
extern void func_02002d14(void *, void *, int, int, int, int);
extern void func_02064af4(void *, void *, int);
extern void func_02002b40(void *, int, int, int);
extern void __arm MI_CpuFill8(void *, int, int);
extern void func_02002a88(void *, int, int, int, int);

extern unsigned char data_ov147_0229ab5c[];
extern unsigned char data_ov147_0229ab70[];
extern unsigned char data_ov147_0229b2ac[];
extern unsigned char data_ov147_0229ab84[];
extern unsigned char data_ov147_0229baac[];
extern unsigned char data_ov147_0229f2ac[];
extern unsigned char data_ov147_0229ab98[];
extern unsigned char data_ov147_0229ae0c[];
extern unsigned char data_ov147_0229abb0[];
extern unsigned char data_ov147_0229b0cc[];
extern unsigned char data_ov147_0229abc8[];
extern unsigned char data_ov147_0229aeec[];
extern void *data_021fbe94;

void func_ov147_02299248(void)
{
    func_0203de6c(1);
    func_020028bc(5, 0, 0, 0);
    func_020029e8(5, 1);
    func_02002d14(data_ov147_0229ab5c, data_021fbe94, 5, 8, 8, 15);
    func_02064af4(data_ov147_0229ab70, data_ov147_0229b2ac, 0x800);
    func_02002b40(data_ov147_0229b2ac, 5, 0x800, 0);
    func_02064af4(data_ov147_0229ab84, data_ov147_0229baac, 0x3800);
    MI_CpuFill8(data_ov147_0229f2ac, 0, 0x3800);
    func_02064af4(data_ov147_0229ab98, data_ov147_0229ae0c, 0xe0);
    func_02064af4(data_ov147_0229abb0, data_ov147_0229b0cc, 0x1e0);
    func_02064af4(data_ov147_0229abc8, data_ov147_0229aeec, 0x1e0);
    func_02002a88(data_ov147_0229f2ac, 5, 0x140, 0x140, 0x2ff);
}
