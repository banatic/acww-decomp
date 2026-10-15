/* func_ov104_0229e924 @ 0x0229e924, 0x54 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern void *data_021fbe94;
extern unsigned char data_ov104_0229f730[];
extern unsigned char data_ov104_0229f750[];
extern unsigned char data_ov104_0229f774[];
extern int func_02002d14(void *data, void *param, int a, int b, int c, int d);
extern int func_02002ca4(void *data, void *param, int a);
extern int func_02002c6c(void *data, void *param, int a, int b, int c, int d);

void func_ov104_0229e924(void *self)
{
    void *p = data_021fbe94;
    func_02002d14(data_ov104_0229f730, p, 4, 4, 4, 4);
    func_02002ca4(data_ov104_0229f750, p, 4);
    func_02002c6c(data_ov104_0229f774, p, 4, 0x1e2, 0x1e2, 0x227);
}
