/* func_ov110_0229d6c4 @ 0x0229d6c4, 0x64 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02209d68(void *p, int a, int b);
extern int func_ov110_0229d3d8(void *p, unsigned char c);
extern int func_ov110_0229d388(void *p, unsigned char c);
extern int func_ov002_02209d38(void *p, int a, int b, int c);
extern int func_ov002_02209d8c(void *p);
extern void func_ov110_0229cd8c(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

unsigned char *func_ov110_0229d6c4(unsigned char *param0, unsigned char param1, int param2)
{
    *(unsigned char *) (param0 + 0xf4) = param1;
    func_ov002_02209d68(param0 + 0x22c8, *(int *) (param0 + 0xa8), *(int *) (param0 + 0xac));
    {
        int ret1 = func_ov110_0229d3d8(param0, param1);
        int ret2 = func_ov110_0229d388(param0, param1);
        func_ov002_02209d38(param0 + 0x22c8, ret1, ret2, param2);
    }
    func_ov002_02209d8c(param0 + 0x22c8);
    func_ov110_0229cd8c(param0);
    return func_ov002_02208098((void *) (param0), 0x10);
}
