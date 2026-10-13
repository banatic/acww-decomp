/* func_0209ec74 @ 0x0209ec74, 0x11c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020d1b90[];

extern void *func_020984e8(void *p);
extern int func_020b65c4(void);
extern void func_0209e7fc(void *p);
extern void func_0204de34(void);
extern void func_0204dde0(void);
extern void func_0209dfc0(void);
extern void func_0207bddc(void *p, int a);
extern void func_0207bbb8(void *p);
extern void func_0207b764(void);
extern void func_0207b594(void *p);
extern void func_020b03f8(void);
extern void func_020b0518(void);
extern void func_0204e938(void *p);
extern void func_0209d7e8(void);
extern void func_0205a2f0(void);
extern int func_0203d470(void);
extern void func_02004634(void *p);
extern void func_02088318(void);
extern void func_02096c88(void);
extern void func_020b10b8(void);
extern void func_020975c4(void);
extern void func_020a128c(void);
extern void func_020ba3ac(void);
extern void func_020ba2e0(void);
extern void func_02087480(void *p);
extern void func_0207a6a0(void *p, int a);
extern void func_0207c754(void *p, int a);
extern int func_0207918c(void);
extern int func_02099020(void *p, int a);
extern void func_02099670(void *p);
extern void func_02088b68(void);
extern void func_0208602c(void);
extern int func_020860c8(void);
extern void func_02087e9c(int r0, int a);
extern void func_02098ff8(void *p, int a);
extern void func_02099050(void *p);
extern void func_0207ac20(void *p);

void func_0209ec74(char *p)
{
    void *ret;

    ret = func_020984e8(p);
    if (func_020b65c4() != 6) {
        func_0209e7fc(p);
        func_0204de34();
        func_0204dde0();
        func_0209dfc0();
        func_0207bddc(p + 0x9284, 0);
    }
    func_0207bbb8(p + 0x9284);
    func_0207b764();
    func_0207b594(p + 0x9284);
    func_020b03f8();
    func_020b0518();
    func_0204e938(p + 0xd304);
    func_0209d7e8();
    func_0205a2f0();
    func_02004634(data_020d1b90[func_0203d470()]);
    func_02088318();
    func_02096c88();
    func_020b10b8();
    func_020975c4();
    func_020a128c();
    func_020ba3ac();
    func_020ba2e0();
    func_02087480(p + 0x17364);
    func_0207a6a0(p + 0x9284, 0);
    func_0207c754(p + 0x9284, 1);
    if (func_020b65c4() == 6) {
        if (func_0207918c() == -1) {
            if (func_02099020(ret, 0x23) == 0) {
                if (func_02099020(ret, 2) != 0) {
                    func_02099670(ret);
                    func_02088b68();
                    func_0208602c();
                    func_02087e9c(func_020860c8(), 1);
                }
            }
        }
    }
    func_02098ff8(ret, 2);
    func_02099050(ret);
    if (func_020b65c4() != 6) {
        func_0207ac20(p + 0x9284);
    }
}
