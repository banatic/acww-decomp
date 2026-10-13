/* func_ov048_02260cd0 @ 0x02260cd0, 0x58 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov048_02260f64(void *p, int a);
extern int func_ov048_02260f30(void *p);
extern void func_02073044(void);
extern int func_020ec920(void);
extern int func_020ec1e8(void);
extern void func_ov048_022616b8(void *p, int a);
extern void func_020ec260(void);
extern void func_02074294(void);

void func_ov048_02260cd0(void *param1)
{
    if (func_ov048_02260f64(param1, 0) != 0) {
        return;
    }
    if (func_ov048_02260f30(param1) != 0) {
        return;
    }
    func_02073044();
    if (func_020ec920() == 0) {
        return;
    }
    if (func_020ec1e8() == 3) {
        goto skip;
    }
    func_020ec1e8();
skip:
    *(unsigned short *) (*(unsigned char **) ((unsigned char *) param1 + 0xb8) + 0xe6e) = 0xc8;
    func_ov048_022616b8(param1, 6);
    func_020ec260();
    func_02074294();
}
