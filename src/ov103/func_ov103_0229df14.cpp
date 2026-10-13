/* func_ov103_0229df14 @ 0x0229df14, 0xd8 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

class CA {
  public:
    unsigned char pad_00[0x8c];
    unsigned char idx;
    void f0();
    void f1();
    void f2();
    void f3();
    void f4();
    void f5();
    void f6();
    void f7();
    void f8();
};

typedef void (CA::*PMF)();

extern PMF data_ov103_0229e1c0, data_ov103_0229e2d0, data_ov103_0229e2c8, data_ov103_0229e2c0, data_ov103_0229e2b8,
    data_ov103_0229e2b0, data_ov103_0229e2a8, data_ov103_0229e220, data_ov103_0229e298;
extern unsigned int data_ov103_0229e340;

extern "C" void func_ov103_0229d90c(CA *self);
extern "C" void func_ov103_0229d8d4(CA *self);

extern "C" int func_ov103_0229df14(CA *self)
{
    static PMF table[9];

    if ((data_ov103_0229e340 & 1) == 0) {
        table[0] = data_ov103_0229e1c0;
        table[1] = data_ov103_0229e2d0;
        table[2] = data_ov103_0229e2c8;
        table[3] = data_ov103_0229e2c0;
        table[4] = data_ov103_0229e2b8;
        table[5] = data_ov103_0229e2b0;
        table[6] = data_ov103_0229e2a8;
        table[7] = data_ov103_0229e220;
        table[8] = data_ov103_0229e298;
        data_ov103_0229e340 |= 1;
    }

    func_ov103_0229d90c(self);
    (self->*table[self->idx])();
    func_ov103_0229d8d4(self);
    return 1;
}
