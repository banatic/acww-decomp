/* func_ov004_0220fb90 @ 0x0220fb90, 0x108 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int m[12];
} Mtx43;

extern Mtx43 data_021fbe48;
extern short data_ov004_02256c40;
extern short data_ov004_02256c3c;
extern int func_ov004_0220e5c8(void *self);
extern void func_020e96c8(Mtx43 *m, int a, int b, int c);
extern void func_020e9774(Mtx43 *m, int a);
extern void func_020e9744(Mtx43 *m, int a);
extern void func_020e9868(Mtx43 *m, int a, int b, int c);
extern int FX_MulFunc(int a, int b);
extern void *func_ov004_0220fde0(void *self);
extern int func_02053658(void *p);
extern void func_ov004_0220fc98(void *self, void *a, int b);

void func_ov004_0220fb90(char *self)
{
    int q;

    if (func_ov004_0220e5c8(self) != 0) {
        func_020e96c8(&data_021fbe48, *(int *) (self + 0x5c), *(int *) (self + 0x60), *(int *) (self + 0x64));
        func_020e9774(&data_021fbe48, data_ov004_02256c40);
        func_020e9744(&data_021fbe48, (short) (*(short *) (self + 0x8e) + data_ov004_02256c3c));
        if (*(int *) (self + 0x784) == 1) {
            func_020e9868(&data_021fbe48, FX_MulFunc(*(int *) (self + 0x150), -0x1000), 0, 0);
        }
        q = 0x64 * func_02053658(func_ov004_0220fde0(self)) - 0x258;
        func_020e9868(&data_021fbe48, 0, q, 0);
        *(Mtx43 *) (self + 0x59c) = data_021fbe48;
    } else {
        func_ov004_0220fc98(self, 0, 0);
        *(Mtx43 *) (self + 0x254) = data_021fbe48;
        if (*(int *) (self + 0x784) == 1) {
            func_020e9868(&data_021fbe48, FX_MulFunc(0x1000 - *(int *) (self + 0x150), 0x1000), 0, 0);
        }
        *(Mtx43 *) (self + 0x59c) = data_021fbe48;
    }
}
