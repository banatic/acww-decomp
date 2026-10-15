/* func_ov106_0229e88c @ 0x0229e88c, 0x54 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int data_021fbe94;
extern int data_ov106_0229f740[];
extern int data_ov106_0229f760[];
extern int data_ov106_0229f784[];

extern int func_02002d14(int *p, int a, int b, int c, int d, int e);
extern int func_02002ca4(int *p, int a, int b);
extern int func_02002c6c(int *p, int a, int b, int c, int d, int e);

void func_ov106_0229e88c(void *self)
{
    int value = data_021fbe94;
    int local1 = 4;
    int local2 = 4;

    func_02002d14(data_ov106_0229f740, value, 4, 4, local1, local2);
    func_02002ca4(data_ov106_0229f760, value, 4);

    local1 = 0x1e2;
    local2 = 0x227;
    func_02002c6c(data_ov106_0229f784, value, 4, local1, local1, local2);
}
