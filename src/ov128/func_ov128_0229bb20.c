/* func_ov128_0229bb20 @ 0x0229bb20, 0x40 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov127_0229989c(char *addr);
extern int func_ov127_02299890(char *addr);
extern void func_ov128_0229ba54(void *p);

void func_ov128_0229bb20(void *p)
{
    int a;
    int b;

    a = func_ov127_0229989c((char *) p + 0x4A4);
    b = func_ov127_02299890((char *) p + 0x4A4);
    *(int *) ((char *) p + 0x2D54) = a & 0xF;
    *(int *) ((char *) p + 0x2D58) = b & 0xF;
    func_ov128_0229ba54(p);
}
