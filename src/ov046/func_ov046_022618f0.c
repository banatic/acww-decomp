/* func_ov046_022618f0 @ 0x022618f0, 0x70 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov046_02260474(void *self);
extern void *data_020ccf94;
extern int func_02073d90(void *a);
extern short *func_0209d358(int a, int b);
extern int func_0209dcac(void);
extern int func_020e8840(void *p);
extern void func_ov046_022619cc(void *self, int a);

int func_ov046_022618f0(void *self)
{
    if (func_ov046_02260474(self)) {
        return 1;
    }

    if (func_02073d90(data_020ccf94) != 0 || func_0209d358(0, 0x4a)[0] != 0 || func_0209dcac() == 2 || func_0209dcac() == 3) {
        return 1;
    }

    if (func_020e8840((unsigned char *) self + 0x738) == 0) {
        *(unsigned short *) ((unsigned char *) self + 0x73c) = 0x18;
        func_ov046_022619cc(self, 2);
    }
    return 1;
}
