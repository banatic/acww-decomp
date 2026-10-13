/* func_020ae190 @ 0x020ae190, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *data_020ccf94;
extern int func_020ae3b8(unsigned int);
extern void func_020ae67c(void);
extern int func_020ae590(void);
extern int func_02073d90(void *);
extern void func_02066694(void *);
extern int func_020644cc(int);
extern void func_020ae774(void *);
extern int func_020ae5bc(int, void *);
extern void func_0203d7c4(int, void *);
extern void *func_02098844(unsigned int, int);
extern int func_02099a28(void);
extern int func_02099020(void *, int);
extern void *func_02099870(void *);
extern void func_02066024(void *, void *, void *, void *, void *, void *);
extern int func_02097a54(void *);
extern void func_020979f0(void *, int);
extern void func_020ae56c(void);
extern void func_020ae75c(void *);
extern void func_02066688(void *);

extern unsigned char data_020e4160[];
extern unsigned char data_020e4164[];
extern unsigned char data_020e419c[];

extern unsigned char data_021dc7bc[];
extern unsigned char data_021f3b30[];

void func_020ae190(void)
{
    struct {
        char c;
        char pad1[0x3];
        char b0[0x34];
        char b1[0x104];
    } locals;
    int i;
    int zero;

    func_020ae3b8((unsigned int) data_021f3b30);
    func_020ae67c();
    func_020ae3b8((unsigned int) data_021f3b30);
    if (func_020ae590() == 0) {
        return;
    }
    if (func_02073d90(data_020ccf94) != 0) {
        return;
    }

    func_02066694(locals.b1);
    locals.c = (char) func_020644cc(3);
    func_020ae774(locals.b0);
    func_020ae5bc(func_020ae3b8((unsigned int) data_021f3b30), locals.b0);
    func_0203d7c4(2, locals.b0);

    zero = 0;
    for (i = 0; i < 4; i++) {
        void *obj;
        void *ret;

        obj = func_02098844((unsigned int) data_021dc7bc, i);
        if (obj == 0) {
            continue;
        }
        if (func_02099a28() == 0) {
            continue;
        }
        if (func_02099020(obj, 0xc) == 0) {
            continue;
        }
        ret = func_02099870(obj);
        func_02066024(locals.b1, &locals.c, (void *) data_020e419c, (void *) data_020e4160, (void *) data_020e4164, ret);
        if (func_02097a54(locals.b1) != 0) {
            continue;
        }
        func_020979f0(locals.b1, zero);
    }

    func_020ae3b8((unsigned int) data_021f3b30);
    func_020ae56c();
    func_020ae75c(locals.b0);
    func_02066688(locals.b1);
}
