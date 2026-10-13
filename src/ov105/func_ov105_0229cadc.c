/* func_ov105_0229cadc @ 0x0229cadc, 0xd4 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov105_0229c320(int a, int b);
extern void func_ov002_02208d30(void *ptr, int a);
extern int func_ov105_0229d59c(int a, int b);
extern int func_0206fe54(int a);
extern void func_ov002_02208d4c(void *ptr, int a, int b);
extern int func_02065ec0(int a);
extern int func_02065f18(int a);
extern void func_ov105_0229cfc0(int a);
extern void func_ov002_02207d24(void *ptr, int a);
extern void func_ov105_0229cbe0(int a, int b);

void func_ov105_0229cadc(int a, int b, int c)
{
    char *base = (char *) a;
    int tmp, res;

    func_ov105_0229c320((int) base, 0x800);
    base[0x2bb] = (char) b;
    func_ov002_02208d30(base + 0x28f0, 4);
    tmp = func_ov105_0229d59c((int) base, b);
    if (func_0206fe54(tmp) != 0) {
        func_ov002_02208d4c(base + 0x28f0, 0, 0);
    }
    res = func_02065ec0(tmp);
    if (res != 0) {
        if (res == 7) {
            func_ov002_02208d4c(base + 0x28f0, 0x17, 1);
        } else {
            func_ov002_02208d4c(base + 0x28f0, 0x14, 1);
        }
    }
    if (func_02065f18(tmp) == 0xfff1) {
        if (res == 3 || res == 6 || res == 1 || res == 4) {
            func_ov002_02208d4c(base + 0x28f0, 0x15, 3);
        }
    }
    func_ov002_02208d4c(base + 0x28f0, 2, 4);
    func_ov105_0229cfc0((int) base);
    if (c == 0) {
        func_ov002_02207d24(base + 0x23bc, 1);
    }
    func_ov105_0229cbe0((int) base, c);
}
