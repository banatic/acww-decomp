/* func_ov126_022a1394 @ 0x022a1394, 0x68 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov124_0229f378(void *, int);
extern int func_02002c6c(int, int, int, int, int, int);
extern void func_ov095_0229c000(void *, const void *);
extern void func_ov126_022a0978(void *);
extern void func_ov095_0229bfd8(void *, int);
extern void func_ov095_0229c01c(int, int);

extern int data_ov126_022a2154;
extern int data_021fbe94;
extern int data_ov126_022a216c;

void func_ov126_022a1394(unsigned char *p)
{
    func_ov124_0229f378(p + 0xb0, 4);
    func_02002c6c((int) &data_ov126_022a2154, data_021fbe94, 4, 0x13d, 0x13d, 0x1e9);
    func_ov095_0229c000(p + 0x19c, &data_ov126_022a216c);
    func_ov126_022a0978(p);
    func_ov095_0229bfd8(p + 0x19c, 6);
    func_ov095_0229c01c((int) (p + 0x19c), 6);
}
