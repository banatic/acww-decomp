/* func_ov004_022286e8 @ 0x022286e8, 0x60 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern char *data_020ccf94;
extern int func_02073908(char *a, int b);
extern void func_02010d64(void *self);
extern void func_02010e58(void *self, int *t, void *p);
extern void func_02089fc8(void *p);

void func_ov004_022286e8(char *self)
{
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_02010d64(self);
    } else {
        int t[3];
        int *q = (int *) (self + 0x7d4);
        t[0] = q[0];
        t[1] = q[1];
        t[2] = q[2];
        func_02010e58(self, t, self + 0x7f0);
        func_02089fc8(self + 0x174);
    }
}
