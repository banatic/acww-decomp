/* func_ov145_0229ab3c @ 0x0229ab3c, 0x94 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov145_0229a7d8(void *);
extern "C" void func_ov145_0229a7b0(void *);

class UnkStruct_0229ab3c {
  public:
    virtual void f0();
    virtual void f1();
    char pad_04[0x88];
    unsigned char index; // offset 0x8c
};

typedef void (UnkStruct_0229ab3c::*PMF)();

extern unsigned int data_ov145_0229afa8;
extern PMF data_ov145_0229afbc[4];
extern PMF data_ov145_0229ade0;
extern PMF data_ov145_0229ad80;
extern PMF data_ov145_0229adf0;
extern PMF data_ov145_0229ade8;

extern "C" int func_ov145_0229ab3c(UnkStruct_0229ab3c *arg)
{
    if (!(data_ov145_0229afa8 & 1)) {
        data_ov145_0229afbc[0] = data_ov145_0229ade0;
        data_ov145_0229afbc[1] = data_ov145_0229ad80;
        data_ov145_0229afbc[2] = data_ov145_0229adf0;
        data_ov145_0229afbc[3] = data_ov145_0229ade8;
        data_ov145_0229afa8 |= 1;
    }
    func_ov145_0229a7d8(arg);
    (arg->*data_ov145_0229afbc[arg->index])();
    func_ov145_0229a7b0(arg);
    return 1;
}
