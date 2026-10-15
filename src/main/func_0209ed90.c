/* func_0209ed90 @ 0x0209ed90, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *func_020984e8(void);
extern void func_0209e7fc(void);
extern void func_0204de34(void);
extern void func_0204dde0(void);
extern void func_0209dfc0(void);
extern int func_02099870(char *p);
extern void func_02095038(int a, char *p);
extern int func_020996b8(char *p);
extern void func_02072c50(int a, int b);
extern void func_02098ff8(char *p, int a);
extern void func_02098fd0(char *p, int a);
extern void func_0207bddc(char *p, int a);
extern void func_0207bbb8(char *p);
extern void func_0207b764(void);
extern void func_0207b594(char *p);
extern int func_020b03f8(void);
extern void func_020b0518(void *);
extern void func_0204e938(char *p);
extern void func_0209d7e8(void);
extern void func_02099188(char *p, int a);
extern void func_020791a4(int a);
extern void func_0207c754(char *p, int a);
extern int func_0208602c(void);
extern int func_020860c8(int);
extern void func_02087eb0(void *);
extern void func_0207ac20(char *p);

void func_0209ed90(char *p)
{
    char *ret;
    int b;
    int ret2;

    ret = func_020984e8();
    asm { add r0, p, #0 }
    func_0209e7fc();
    func_0204de34();
    func_0204dde0();
    func_0209dfc0();
    func_02095038(func_02099870(ret), p + 2);
    ret2 = func_020996b8(ret);
    b = func_02099870(ret);
    func_02072c50(ret2, b);
    func_02098ff8(ret, 1);
    func_02098ff8(ret, 0x23);
    func_02098fd0(ret, 9);
    func_0207bddc(p + 0x9284, 0);
    func_0207bbb8(p + 0x9284);
    func_0207b764();
    func_0207b594(p + 0x9284);
    func_020b0518((void *) func_020b03f8());
    func_0204e938(p + 0xd304);
    func_0209d7e8();
    func_02099188(ret, 0);
    func_020791a4(-1);
    func_0207c754(p + 0x9284, 1);
    func_02087eb0((void *) func_020860c8((int) func_0208602c()));
    func_0207ac20(p + 0x9284);
}
