/* func_ov104_0229e75c @ 0x0229e75c, 0x5c bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern void func_ov002_02208098(void *, int);
extern int func_ov104_0229c364(void *, int);
extern int func_ov104_0229d6a4(void *);
extern void func_ov104_0229dc20(void *, unsigned char);
extern void func_ov002_022096d8(void *, int);
extern void func_ov002_02207d24(void *, int);

void func_ov104_0229e75c(void *arg)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098(arg, 6);
        return;
    }
    if (func_ov104_0229c364(arg, 4) == 0) {
        return;
    }
    if (func_ov104_0229d6a4(arg) == 0) {
        return;
    }
    func_ov104_0229dc20(arg, *(unsigned char *) ((char *) arg + 0xb5));
    func_ov002_022096d8((char *) arg + 0x2504, 0);
    func_ov002_02207d24((char *) arg + 0x23b8, 1);
}
