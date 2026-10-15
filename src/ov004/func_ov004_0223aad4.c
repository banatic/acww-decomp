/* func_ov004_0223aad4 @ 0x0223aad4, 0xa8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02064b2c(void *, void *, int, int);
extern unsigned int func_021077e8(unsigned int *);
extern int func_02056064(int, int);
extern int func_020561cc(int, int);
extern void func_020e9898(void *);
extern void func_ov004_0223ad7c(void *, int);
extern char *func_02003ea0(void);
extern int func_020ea0e0(void *, void *);
extern int func_ov004_0223a968(void *);
extern int func_ov004_0223a87c(void *);
extern int func_ov004_0223aa30(void *, int, int);
extern char data_ov004_02256060;
extern void *data_021fbe94;
extern int data_021c9b24;
extern unsigned char data_ov004_022595b8;

void func_ov004_0223aad4(char *self)
{
    void *h;
    int a;
    *(short *) self = -1;
    *(int *) (self + 0x154) = 0;
    h = func_02064b2c(&data_ov004_02256060, data_021fbe94, 4, 0);
    if (h != 0) {
        int t = (int) func_021077e8((unsigned int *) h);
        func_02056064(t, 0);
        *(int *) (self + 0x154) = func_020561cc(t, data_021c9b24);
        func_020e9898(h);
    }
    func_ov004_0223ad7c(self + 4, *(int *) (self + 0x154));
    func_ov004_0223ad7c(self + 0xac, *(int *) (self + 0x154));
    if (data_ov004_022595b8 != 0) {
        *(int *) (self + 0x158) = func_020ea0e0(func_02003ea0() + 0x60, data_021fbe94);
    }
    a = func_ov004_0223a968(self);
    func_ov004_0223aa30(self, a, func_ov004_0223a87c(self));
}
