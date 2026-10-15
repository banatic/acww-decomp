/* func_ov096_0229f90c @ 0x0229f90c, 0x64 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02209d68(void *p, int a, int b);
extern int func_ov096_0229f290(void *p, unsigned char c);
extern int func_ov096_0229f200(void *p, unsigned char c);
extern int func_ov002_02209d38(void *p, int a, int b, int c);
extern int func_ov002_02209d8c(void *p);
extern void func_ov096_0229ea34(void *p);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

unsigned char *func_ov096_0229f90c(unsigned char *param0, unsigned char param1, int param2)
{
    *(unsigned char *) (param0 + 0xb4) = param1;
    func_ov002_02209d68(param0 + 0x24e8, *(int *) (param0 + 0xa4), *(int *) (param0 + 0xa8));
    {
        int ret1 = func_ov096_0229f290(param0, param1);
        int ret2 = func_ov096_0229f200(param0, param1);
        func_ov002_02209d38(param0 + 0x24e8, ret1, ret2, param2);
    }
    func_ov002_02209d8c(param0 + 0x24e8);
    func_ov096_0229ea34(param0);
    return func_ov002_02208098((void *) (param0), 0x1b);
}
