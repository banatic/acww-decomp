/* func_020769b8 @ 0x020769b8, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int *data_020ccf94;         // 0x020ccf94
extern int data_021e5a2c;          // 0x021e5a2c
extern const char data_021dc7aa[]; // 0x021dc7aa

extern void func_020736bc(int *p, int *out, int val);
extern void func_020789f4(int *out1, int *out2, int *in);
extern int func_0207cec0(int *base, int val);
extern void *func_020807c0(int cond, int val);
extern int func_020984fc(int val);
extern int func_02099870(int val);
extern void func_02081e14(void *obj, int val, const char *str, int flag);

void func_020769b8(int a, int b, int c, int d)
{
    int loc0, loc1, loc2;
    int cond;
    void *ptr;

    func_020736bc(data_020ccf94, &loc0, a);
    func_020789f4(&loc1, &loc2, &loc0);
    cond = func_0207cec0(&data_021e5a2c, loc1);
    if (cond != 0) {
        ptr = func_020807c0(cond, loc2);
        if (ptr != 0) {
            func_02081e14(ptr, func_02099870(func_020984fc(d)), data_021dc7aa, 0);
        }
    }
}
