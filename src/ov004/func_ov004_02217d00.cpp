/* func_ov004_02217d00 @ 0x02217d00, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct D {
    int a, b;
    ~D() {}
};

extern "C" {
extern void func_0203ee14(void *self, void *base);
extern void func_020a8164(void *p, void *tbl);
extern int func_020a12d4(void);
extern int func_020a12c0(void);
extern int data_ov004_02253210;
extern int data_ov004_02253224;
}

extern "C" int func_ov004_02217d00(char *self)
{
    D t;
    char *q;

    q = self;
    if (self != 0) {
        q = q + 0xec;
    }
    func_0203ee14(self, q);
    *(int *) (*(int *) (self + 0x12c) + 8) = 1;
    if (func_020a12d4() != 0 || func_020a12c0() != 0) {
        func_020a8164(self + 0xec, &data_ov004_02253210);
        *(char *) (self + 0x10a) = 0x19;
    } else {
        func_020a8164(self + 0xec, &data_ov004_02253224);
        *(char *) (self + 0x10a) = 0;
    }
    return 1;
}
