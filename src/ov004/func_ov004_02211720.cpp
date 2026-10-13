/* func_ov004_02211720 @ 0x02211720, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct D {
    int a, b;
    ~D() {}
};

extern "C" {
extern void func_0203ee14(void *self, void *base);
extern void func_020a8164(void *p, void *tbl);
extern int data_ov004_02253184;
}

extern "C" int func_ov004_02211720(char *self)
{
    D t;
    char *q;

    q = self;
    if (self != 0) {
        q = q + 0xec;
    }
    func_0203ee14(self, q);
    *(int *) (*(int *) (self + 0x12c) + 8) = 1;
    func_020a8164(self + 0xec, &data_ov004_02253184);
    *(char *) (self + 0x10a) = 0;
    return 1;
}
