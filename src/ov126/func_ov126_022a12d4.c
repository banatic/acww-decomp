/* func_ov126_022a12d4 @ 0x022a12d4, 0xc0 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov095_0229b324(void *receiver);
extern void func_ov124_0229ef4c(void *ptr, int val);
extern int func_02002d14(void *a, int b, int c, int d, int e, int f);
extern void func_ov002_0220af94(void *receiver);
extern int func_ov126_0229f7c8(void *self, int val);
extern void *func_02070c08(void *ptr);
extern void func_020a8c1c(void *ptr);
extern int func_020b496c(int a, void *ptr);
extern int func_0206fca4(void);
extern int func_0207094c(void *ptr, int val);
extern void func_02070adc(void *ptr, int a, int b, int c, int d, int e, int f);
extern void func_02070a04(void *ptr, int a, int b);
extern int **func_02070be8(void *ptr);
extern unsigned char data_ov126_022a2140[];
extern int data_021fbe94;

static __inline char *get_3ff4(char *self)
{
    return self + 0x3ff4;
}

void func_ov126_022a12d4(char *self)
{
    unsigned char local[0x6c];
    int ret;
    int res;

    func_ov095_0229b324(self + 0x19c);
    func_ov124_0229ef4c(self + 0xb0, 6);
    func_02002d14(data_ov126_022a2140, data_021fbe94, 8, 5, 5, 5);
    func_ov002_0220af94(self + 0x3dc4);
    if (func_ov126_0229f7c8(self, 0x100) != 0) {
        func_02070c08(local);
        func_020a8c1c(local);
        ret = func_020b496c(0, local);
        res = func_0206fca4();
        if (res == 0x12) {
            func_0207094c(get_3ff4(self), 0x80);
        } else {
            func_0207094c(get_3ff4(self), 0x66);
        }
        func_02070adc(get_3ff4(self), 8, 0x1c0, 6, 15, 0, 0);
        func_02070a04(get_3ff4(self), 0, 0);
        func_02070be8(local);
    }
}
