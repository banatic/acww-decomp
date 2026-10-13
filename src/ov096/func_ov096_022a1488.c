/* func_ov096_022a1488 @ 0x022a1488, 0xb8 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

#pragma arm
extern int func_020ee45c(void *p);
#pragma thumb
extern void func_ov094_0229af40(void *p, int a);
extern void func_ov094_0229bbd8(void *p, int a);
extern void func_ov094_0229a2b0(void *p, int a);
extern void func_ov002_02207cec(void *p, int a);
extern void func_ov002_02209e18(void *p);
extern void func_ov096_0229e6a0(void *p);
extern int func_0206fb9c(void);
extern void func_ov002_02209984(void *p, int a, int b, int c);
extern void func_ov002_02208e38(void *p);
extern void func_0206e2ec(void *p, int a);
extern int func_ov090_02298f74(int a);
extern void func_ov096_0229c2ec(void *p, unsigned int a);

void func_ov096_022a1488(unsigned char *p)
{
    *(unsigned int *) (p + 0x94) = 0;
    func_ov094_0229af40(p + 0x358, 2);
    func_ov094_0229bbd8(p + 0xdb8, 2);
    func_ov094_0229a2b0(p + 0xde0, 6);
    *(unsigned char *) (p + 0xb3) = 0x26;
    func_ov002_02207cec(p + 0x2418, 2);
    func_ov002_02209e18(p + 0x24e8);
    func_ov096_0229e6a0(p);
    *(unsigned char *) (p + 0xb5) = (unsigned char) func_0206fb9c();
    func_ov002_02209984(p + 0x2564, 3, 1, 0);
    func_ov002_02208e38(p + 0x2564);
    func_0206e2ec(p + 0x2a74, 3);
    *(unsigned char *) (p + 0xc2) = 0;
    if (func_ov090_02298f74(func_020ee45c(p)) != 0) {
        func_ov096_0229c2ec(p, 0x80000);
    }
}
