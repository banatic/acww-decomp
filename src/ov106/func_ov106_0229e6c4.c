/* func_ov106_0229e6c4 @ 0x0229e6c4, 0x70 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206f56c(void);
extern int func_ov106_0229c364(void *, int);
extern int func_ov106_0229cf8c(void);
extern void func_ov106_0229d5c4(void *, unsigned char);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov002_022096d8(void *, int);
extern int func_ov002_02207d24(void *, int);
extern unsigned char data_021fbdd8;

void func_ov106_0229e6c4(void *param)
{
    if (func_0206f56c()) {
        func_ov002_02208098((void *) (param), 6);
        return;
    }
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (param), 6);
        return;
    }
    if (func_ov106_0229c364(param, 4) == 0) {
        return;
    }
    // clang-format off
    asm {
        mov r0, param
    }
    // clang-format on
    if (func_ov106_0229cf8c() == 0)
    {
        return;
    }
    func_ov106_0229d5c4(param, *((unsigned char *) param + 0xB5));
    func_ov002_022096d8((char *) param + 0x2304, 0);
    func_ov002_02207d24((char *) param + 0x21B8, 1);
}
