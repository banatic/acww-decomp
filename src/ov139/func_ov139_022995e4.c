/* func_ov139_022995e4 @ 0x022995e4, 0x68 bytes, Thumb, module ov139
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov139_02299744(void);
extern void func_020a8c1c(void);
extern void func_020708e4(int, int, int);
extern void func_02070adc(int, int, int, int, int, int, int);
extern void func_02070a04(int, int, int);

void func_ov139_022995e4(int a0, int a1, int a2, int a3)
{
    int local0;
    int a, b;
    int r2;

    local0 = func_ov139_02299744();

    if (a2 == 0) {
        func_020a8c1c();
    } else {
        func_020708e4(local0, a2, 6);
    }

    r2 = a1 * 16 + 0x1d2;

    a = 0xF;
    b = 0xE;
    if (a3 != 0xFF) {
        a = a3;
        b = 0xF;
    }

    func_02070adc(local0, *(unsigned char *) ((char *) a0 + 0x9a2), r2, 8, a, b, 0);
    func_02070a04(local0, 1, 0);
}
