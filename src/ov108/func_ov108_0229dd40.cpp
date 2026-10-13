/* func_ov108_0229dd40 @ 0x0229dd40, 0xa0 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229dd40 {
  public:
    virtual void vf0();
    unsigned char pad_04[0x88];
    unsigned char idx;
};

typedef void (UnkStruct_0229dd40::*PMF)();

extern PMF data_ov108_0229dfa0;
extern PMF data_ov108_0229e088;
extern PMF data_ov108_0229e000;
extern PMF data_ov108_0229e078;
extern PMF data_ov108_0229e070;

extern "C" void func_ov108_0229d8bc(UnkStruct_0229dd40 *self);
extern "C" void func_ov108_0229d884(UnkStruct_0229dd40 *self);

extern "C" int func_ov108_0229dd40(UnkStruct_0229dd40 *self)
{
    static PMF table[5] = {data_ov108_0229dfa0, data_ov108_0229e088, data_ov108_0229e000, data_ov108_0229e078,
                           data_ov108_0229e070};
    func_ov108_0229d8bc(self);
    (self->*table[self->idx])();
    func_ov108_0229d884(self);
    return 1;
}
