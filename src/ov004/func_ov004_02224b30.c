/* func_ov004_02224b30 @ 0x02224b30, 0xac bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec58(void *self);
extern char *data_020ccf94;
extern int func_02073d90(void *g);
extern short *func_0209d358(int a, int b);
extern int func_020a7278(void);
extern void func_ov004_022249b4(void *self, int a);
extern int func_02073dd4(char *g, int a);
extern void func_02003348(int a, int b, void *c, void *d, int e);
extern char *data_ov004_022580dc;
extern int data_ov004_02247760;
extern int data_ov004_02247758;

int func_ov004_02224b30(char *self)
{
    if (func_0202ec58(self) == 0) {
        return 0;
    }
    data_ov004_022580dc = self;
    *(short *) (self + 0x714) = *(short *) (self + 0x8e);
    *(int *) (self + 0x4e8) |= 2;
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        if (func_020a7278() != 0) {
            func_ov004_022249b4(self, 0);
        } else {
            func_ov004_022249b4(self, 5);
        }
    } else {
        func_ov004_022249b4(self, 0);
    }
    if (func_02073dd4(data_020ccf94, *(int *) (data_020ccf94 + 0x64)) == 0) {
        func_02003348(0x66, 0xd01d, &data_ov004_02247760, &data_ov004_02247758, 0);
    }
    return 1;
}
