/* func_0209eac8 @ 0x0209eac8, 0xac bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020984e8(void *p);
extern void func_0209e7fc(unsigned char *p);
extern void func_0204de34(void);
extern void func_0204dde0(void);
extern void func_0209dfc0(void);
extern void func_0209e974(unsigned char *p);
extern void func_02098ff8(void *buf, int n);
extern void func_02098fd0(void *buf, int n);
extern void func_02099188(void *buf, int n);
extern void func_0207bddc(unsigned char *p, int n);
extern void func_0207bbb8(unsigned char *p);
extern void func_0207b764(void);
extern void func_0207b594(unsigned char *p);
extern void func_020b03f8(void);
extern void func_020b0518(void);
extern void func_0204e938(unsigned char *p);
extern void func_0209d7e8(void);
extern void func_020791a4(int v);
extern void func_0207c754(unsigned char *p, int v);
extern void func_0208602c(void);
extern void func_020860c8(void);
extern void func_02087eb0(void);
extern void func_0207ac20(unsigned char *p);

void func_0209eac8(unsigned char *p)
{
    int unused;
    void *buf;

    (void) &unused;

    buf = func_020984e8(p);
    func_0209e7fc(p);
    func_0204de34();
    func_0204dde0();
    func_0209dfc0();
    func_0209e974(p);
    func_02098ff8(buf, 1);
    func_02098ff8(buf, 0x23);
    func_02098fd0(buf, 9);
    func_0207bddc(p + 0x9284, 0);
    func_0207bbb8(p + 0x9284);
    func_0207b764();
    func_0207b594(p + 0x9284);
    func_020b03f8();
    func_020b0518();
    func_0204e938(p + 0xd304);
    func_0209d7e8();
    func_02099188(buf, 0);
    func_020791a4(-1);
    func_0207c754(p + 0x9284, 1);
    func_0208602c();
    func_020860c8();
    func_02087eb0();
    func_0207ac20(p + 0x9284);
}
