/* func_ov004_0224564c @ 0x0224564c, 0xf8 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct Controller {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void f19();
    virtual void *position();
};
struct Pane {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void update();
};
struct Vec {
    int x, y, z;
};
struct Pair {
    int x, y;
};
extern "C" {
extern Controller *func_ov004_022318f8(void);
extern char *func_02096190(unsigned int);
extern void func_0203aa24(int *, int *, void *);
extern void RtcSendPxiCommand(int);
extern void func_0208e594(void *, int, int);
extern Pair data_ov004_0224be24[], data_ov004_0224be14;
extern unsigned char data_021c75b8;
}
static inline int special_mode()
{
    return data_021c75b8 == 2;
}
extern "C" void func_ov004_0224564c(unsigned char *self)
{
    // One aggregate retains the zero stores when its coordinate addresses escape.
    struct {
        int x, y;
        Vec unused;
    } local;
    local.unused.x = 0;
    local.unused.y = 0;
    local.unused.z = 0;

    void *p;
    if (self[0x31d]) {
        p = func_ov004_022318f8()->position();
    } else {
        p = func_02096190(self[0x31c]) + 0x5c;
    }
    func_0203aa24(&local.x, &local.y, p);
    if (!self[0x31d]) {
        local.x += data_ov004_0224be24[self[0x31c]].x;
        local.y += data_ov004_0224be24[self[0x31c]].y;
    } else {
        local.x += data_ov004_0224be14.x;
        local.y += data_ov004_0224be14.y;
    }
    if (special_mode() && *(int *) (self + 0x320) == 2 &&
        (*(int *) (self + 0x330) != local.x || *(int *) (self + 0x334) != local.y)) {
        RtcSendPxiCommand(11);
    }
    func_0208e594(self + 0x50, local.x, local.y);
    ((Pane *) (self + 0x50))->update();
    *(int *) (self + 0x330) = local.x;
    *(int *) (self + 0x334) = local.y;
}
