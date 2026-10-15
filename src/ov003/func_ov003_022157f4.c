/* func_ov003_022157f4 @ 0x022157f4, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02215894(char *p);
extern int func_0205e8d8(char *p);
extern int func_0200f290(char *p, int a);
extern int func_020604f8(char *p);
extern void func_ov003_0222ad2c(void *object);
extern int func_ov003_02228400(char *p, int a);
extern void *func_ov003_02215624(char *p, int a, int b, int c);
extern int func_020b6590(void);
extern int func_020b758c(int a, int b);
extern int func_020604c8(char *p);
extern void *func_ov003_02215760(char *p, int a, int b);

void func_ov003_022157f4(char *p)
{
    void *condition_value_1;
    func_ov003_02215894(p);
    if (func_0205e8d8(p + 0x5a0) == 0) {
        return;
    }
    if (func_0200f290(p, 0xb) != 0) {
        condition_value_1 = (void *) (func_020604f8(p + 0x5c8));
        if (condition_value_1 != 0) {
            func_ov003_0222ad2c(condition_value_1);
        } else {
            func_ov003_02228400(p + 0x5d0, 0x1000);
        }
        func_ov003_02215624(p, 0, 6, -1);
    } else {
        if (*(unsigned char *) (p + 0x140) == 0 && func_020b758c(func_020b6590(), 0) == 0) {
            return;
        }
        if (func_020604c8(p + 0x5c8) != 0) {
            func_ov003_02215760(p, 6, -1);
        } else {
            func_ov003_02215624(p, 0, 6, -1);
        }
    }
}
