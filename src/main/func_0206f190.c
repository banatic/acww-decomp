/* func_0206f190 @ 0x0206f190, 0xb4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern unsigned int data_021fbe94;
extern void *func_020e9958(unsigned int, int);
extern int func_0203d064(void *, void *, int);
extern void *func_0203cfd0(void *);
extern void func_0206eb1c(void *, void *);
extern void *func_0203cfe4(void *);
extern void func_0200268c(void *, void *, int, int);
extern void func_020e993c(unsigned int, void *);
extern int func_020b99a0(void *, void *, int, int, int, int, void *, int);
extern void func_0209939c(int, void *);

void func_0206f190(unsigned short *a0, void *a1, void *a2, void *a3)
{
    int A;
    int flag;
    unsigned int v;
    unsigned int B;
    void *C;

    A = func_020984e8();
    flag = 0;
    v = *a0;
    if (v >= 0x11a8 && v <= 0x12a7) {
        flag = 1;
    }
    if (!flag) {
        if (v < 0x12a8 || v > 0x12af) {
            return;
        }
    }
    B = data_021fbe94;
    C = func_020e9958(B, 0x2c4);
    if (C == 0) {
        return;
    }

    func_0203d064(C, a0, A);
    func_0206eb1c(func_0203cfd0(C), a3);
    func_0200268c(func_0203cfe4(C), a2, 4, 4);
    func_020e993c(B, C);
    if (func_020b99a0(a1, a2, 5, 0, 0, 0xf, a3, 0) != 0) {
        func_0209939c(A, a0);
    }
}
