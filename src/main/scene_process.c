/* scene_process: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020b6ae0 @ 0x020b6ae0, 0x12c bytes, Thumb
 * func_020b6a7c @ 0x020b6a7c, 0x64 bytes, Thumb
 * func_020b6a2c @ 0x020b6a2c, 0x50 bytes, Thumb
 * func_020b6a28 @ 0x020b6a28, 0x2 bytes, Thumb
 */

struct UnkStruct_020b6ae0 {
    unsigned char pad_00[0x68];
    int unk_68;
};

extern void func_020351ec(void);
extern int func_020b6590(void);
extern void func_020b7e6c(void *);
extern void func_0205c188(void);
extern void func_02082c4c(void);
extern void func_02078d88(void);
extern void func_020826d0(void);
extern void func_02060934(void);
extern void func_0205f6dc(void);
extern void func_0205f994(void);
extern void func_0205e0d8(void);
extern void func_0205e898(void);
extern void func_0205d21c(void);
extern void func_0205f808(void);
extern void func_0205dc40(void);
extern void func_0205daf8(void);
extern void func_0205dd80(void);
extern void func_0205d70c(void);
extern void func_0205cf6c(void);
extern int func_02072614(void);
extern void func_02072638(void *);
extern void func_02053e4c(void);
extern int func_02062ad4(void);
extern void func_020ace0c(void);
extern void func_020ad3a0(void);
extern int func_0203750c(void);
extern int func_020375a0(void *);
extern void func_020b68e4(void);
extern int func_020b65c4(void);
extern void func_020962a4(int, int);
extern void func_02096294(int);
extern int func_020a6ed0(void);
extern int func_0209847c(int);
extern void func_02099a38(void *);
extern void func_020a6ec0(int);
extern void func_020b70e8(void);
extern void func_020b7218(void);
extern int data_021c8ca0;
extern int data_021d3124;
extern int data_021f6948;
extern unsigned char data_020e54a8;
extern struct UnkStruct_020b6ae0 *data_020ccf94;
extern void func_02030dcc(void);
extern void func_0208a0a0(void);
extern unsigned char data_021c75b8;
extern unsigned char data_021c75b0;
extern int data_021f69d0;
extern void *func_020b5e84(void *);
extern int func_020b64c0(void *);
extern void *func_020b5e10(void);
extern int func_020b5e20(void *);
extern int func_020b5e18(void *);
extern void func_020b5e44(int, int);
extern void func_020b698c(void *object);
extern void NNS_G3dGeFlushBuffer(void);
extern void func_020b75b8(int, unsigned char, unsigned char, int);
extern void func_020348f8(void);
extern void func_02089ce0(void);
extern unsigned char data_021fbdd8;
extern unsigned short data_021fbde0;
extern unsigned short data_021fbde4;

int func_020b6ae0(void)
{
    void *condition_value0;
    func_020351ec();
    func_020b7e6c((void *) func_020b6590());
    data_021c8ca0 = 0;
    func_0205c188();
    func_02082c4c();
    func_02078d88();
    func_020826d0();
    func_02060934();
    func_0205f6dc();
    func_0205f994();
    func_0205e0d8();
    func_0205e898();
    func_0205d21c();
    func_0205f808();
    func_0205dc40();
    func_0205daf8();
    func_0205dd80();
    func_0205d70c();
    func_0205cf6c();
    func_02072638((void *) func_02072614());
    func_02053e4c();
    func_02062ad4();
    func_020ace0c();
    func_020ad3a0();
    func_020375a0((void *) func_0203750c());
    func_020b68e4();
    data_021d3124 = 0;

    if (func_020b65c4() == 6) {
        unsigned int i;
        struct UnkStruct_020b6ae0 *p;
        for (i = 0, p = data_020ccf94; i < 4; i++) {
            if (i == 0) {
                func_020962a4(0, p->unk_68);
                p->unk_68 = 0;
            } else {
                func_02096294(i);
            }
        }
    } else if (func_020b65c4() == 7) {
        int j;
        for (j = 2; j >= 0; j--) {
            func_02096294(j + 1);
        }
    } else if (func_020b65c4() == 14) {
        int r = func_020a6ed0();
        if (r > 0 && r < 4) {
            if ((condition_value0 = (void *) (func_0209847c(r + 3)))) {
                func_02099a38(condition_value0);
            }
            func_02096294(r);
        }
        func_020a6ec0(4);
    }

    func_020b70e8();
    data_021f6948 = 0;
    func_020b7218();
    data_020e54a8 = 2;
    return 1;
}

int func_020b6a7c(int a0)
{
    unsigned int ok;
    int st;

    func_02030dcc();
    func_0208a0a0();
    if (data_021c75b8 == 2) {
        ok = 1;
    } else {
        ok = 0;
    }
    if (ok == 0) {
        if (data_021c75b0 == 0) {
            return 1;
        }
    }
    if (func_020b64c0(func_020b5e84(&data_021f69d0)) != 0) {
        st = func_020b5e20(func_020b5e10());
        func_020b5e44(st, func_020b5e18(func_020b5e10()));
    }
    return 1;
}

int func_020b6a2c(void *object)
{
    int first_arg;
    int flag;
    unsigned char u1;
    unsigned char u2;

    first_arg = 0;
    flag = 0;
    u1 = 0;
    u2 = 0;

    func_020b698c(object);
    NNS_G3dGeFlushBuffer();
    first_arg = func_020b6590();
    flag = (data_021fbdd8 != 0);
    u1 = (unsigned char) data_021fbde0;
    u2 = (unsigned char) data_021fbde4;
    func_020b75b8(first_arg, u1, u2, flag);
    func_020348f8();
    func_02089ce0();
    return 1;
}

void func_020b6a28(void) {}
