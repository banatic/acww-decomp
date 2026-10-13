/* func_ov046_02261aa0 @ 0x02261aa0, 0x90 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void);
extern void func_ov046_02261268(char *addr, int val);
extern int func_0209dcac(void);
extern int func_02073d90(int value);
extern short *func_0209d358(int a, int b);
extern void func_ov046_022619cc(char *addr, int val);
extern int data_020ccf94;

int func_ov046_02261aa0(char *p)
{
    if (func_0202ec58() == 0) {
        return 0;
    }
    *(short *) (p + 0x73a) = *(short *) (p + 0x8e);
    *(short *) (p + 0x73c) = 0;
    *(int *) (p + 0x4e8) |= 2;
    func_ov046_02261268(p + 0x658, 5);
    if (func_0209dcac() == 2 || func_0209dcac() == 3 || func_02073d90(data_020ccf94) != 0) {
        goto call0;
    }
    if (func_0209d358(0, 0x4a)[0] == 0) {
        goto call2;
    }
call0:
    func_ov046_022619cc(p, 0);
    goto ret;
call2:
    func_ov046_022619cc(p, 2);
ret:
    return 1;
}
