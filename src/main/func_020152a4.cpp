/* func_020152a4 @ 0x020152a4, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
extern void func_02068440(void *a);
extern int func_02019e00(void *a);
extern int func_02019de8(void *a);
extern int func_02019b80(void *s, int value, unsigned short *src, int a, unsigned char b, int c, int d);
extern void func_0201600c(void *self);
}

class UnkStruct_020152a4 {
  public:
    virtual int f0();
    virtual int f1();
    virtual int f2();
    virtual int f3();
    virtual int f4();
    virtual int f5();
    virtual int f6();
    virtual int f7();
    virtual int f8();
    virtual int f9();
    virtual int f10();
    virtual int f11();
    virtual int f12();
    virtual int f13();
    virtual int f14(int);
};

extern "C" int func_020152a4(void *selfv)
{
    char *self = (char *) selfv;

    if (*(void **) (self + 0x4c) == 0) {
        goto ret0;
    }

    if (*(void **) (self + 0x40) != 0) {
        func_02068440(*(void **) (self + 0x40));
    }

    if (func_02019e00((char *) (*(void **) (self + 0x4c)) + 0x564) != 8) {
        goto part2;
    }

    if (func_02019de8((char *) (*(void **) (self + 0x4c)) + 0x564) != 0) {
        goto part2;
    }

    ((UnkStruct_020152a4 *) self)->f14(0);
    goto ret0;

part2:
    if (*(void **) (self + 0x40) == 0) {
        goto ret0;
    }

    if (func_02019b80((char *) (*(void **) (self + 0x4c)) + 0x564, 4, (unsigned short *) (self + 0x7e), *(int *) (self + 0x80),
                      *(unsigned char *) (self + 0x94), *(int *) (self + 0x98), *(int *) (self + 0x48)) == 0) {
        goto ret0;
    }

    func_0201600c(self);
    *(unsigned char *) (self + 0xac) = 1;

ret0:
    return 0;
}
