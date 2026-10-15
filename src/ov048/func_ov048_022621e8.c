/* func_ov048_022621e8 @ 0x022621e8, 0x64 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern void func_020732b4(int a, int b);
extern int func_020ec1e8(void);
extern void func_ov048_02262320(void *self);
extern void func_ov048_02262390(void *self, int a);
extern void func_02073100(void);
extern int func_020eb704(int val);
extern void func_ov048_022616b8(void *self, int a);
extern int data_020ccf94;

void func_ov048_022621e8(void *self)
{
    int val;

    func_020732b4(data_020ccf94, 1);
    if (func_020ec1e8() != 4) {
        func_ov048_02262320(self);
    } else {
        func_ov048_02262390(self, 1);
        val = *(int *) ((char *) self + 0x3ec);
        func_02073100();
        func_020eb704(val);
        *(short *) (*(char **) ((char *) self + 0xb8) + 0xe6e) = 0x960;
        func_ov048_022616b8(self, 5);
    }
}
