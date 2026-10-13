/* func_ov101_0229d0a8 @ 0x0229d0a8, 0x50 bytes, Thumb, module ov101
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_0220909c(char *addr);
extern void func_ov002_022096d8(char *addr, int val);
extern void func_ov002_02207d24(char *addr, int val);
extern int func_0208e4bc(char *addr);
extern void func_ov101_0229c6a0(char *obj);
extern void func_ov002_02208098(char *obj, int val);

void func_ov101_0229d0a8(char *obj)
{
    if (func_ov002_0220909c(obj + 0x2300) == 0) {
        return;
    }
    func_ov002_022096d8(obj + 0x2300, 0);
    func_ov002_02207d24(obj + 0x21b4, 1);
    if (func_0208e4bc(obj + 0x229c) != 0) {
        func_ov101_0229c6a0(obj);
    }
    func_ov002_02208098(obj, 0x15);
}
