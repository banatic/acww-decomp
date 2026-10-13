/* func_ov125_022a07fc @ 0x022a07fc, 0xa0 bytes, Thumb, module ov125
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
void func_ov125_022a04a0(void *self);
void func_ov125_022a0474(void *self);
}

class UnkStruct_022a07fc {
  public:
    unsigned char pad_00[0x8c];
    unsigned char idx;
    void m0();
    void m1();
    void m2();
    void m3();
    void m4();
};

typedef void (UnkStruct_022a07fc::*PMF)();

extern PMF data_ov125_022a0a90;
extern PMF data_ov125_022a0a20;
extern PMF data_ov125_022a0aa8;
extern PMF data_ov125_022a0aa0;
extern PMF data_ov125_022a0a98;

extern "C" int func_ov125_022a07fc(UnkStruct_022a07fc *self)
{
    static PMF table[5] = {data_ov125_022a0a90, data_ov125_022a0a20, data_ov125_022a0aa8, data_ov125_022a0aa0,
                           data_ov125_022a0a98};
    func_ov125_022a04a0(self);
    (self->*table[self->idx])();
    func_ov125_022a0474(self);
    return 1;
}
