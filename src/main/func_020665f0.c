/* func_020665f0 @ 0x020665f0, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void);
extern void func_02066650(char *a);
extern void *func_02099870(void *x);
extern void func_020951dc(void *x, char *p);
extern void func_02065eac(char *a, int x);
extern void *func_02099734(void *x);
extern void *func_02098ddc(void *x);
extern void func_02065e10(char *a, char *p);

void func_020665f0(char *a, int b)
{
    void *v0;

    v0 = func_020984e8();
    func_02066650(a);
    *(a + 0xf9) = (char) b;
    *(a + 0xfb) = 0;
    *(a + 0x42) = 2;
    func_020951dc(func_02099870(v0), a + 0x24);
    func_02065eac(a, 1);
    func_02065e10(a, (char *) func_02098ddc(func_02099734(v0)) + 0x28);
}
