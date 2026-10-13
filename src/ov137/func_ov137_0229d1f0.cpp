/* func_ov137_0229d1f0 @ 0x0229d1f0, 0x94 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229d1f0 {
  public:
    unsigned char pad_00[0x8c];
    unsigned char m_index;
};

typedef void (UnkStruct_0229d1f0::*PMF)();

extern unsigned int data_ov137_0229d4a0;
extern PMF data_ov137_0229d4a8[];
extern PMF data_ov137_0229d3a8;
extern PMF data_ov137_0229d3a0;
extern PMF data_ov137_0229d3b0;
extern PMF data_ov137_0229d430;

extern "C" void func_ov137_0229cf0c(UnkStruct_0229d1f0 *self);
extern "C" void func_ov137_0229cefc(UnkStruct_0229d1f0 *self);

extern "C" int func_ov137_0229d1f0(UnkStruct_0229d1f0 *self)
{
    if ((data_ov137_0229d4a0 & 1) == 0) {
        data_ov137_0229d4a8[0] = data_ov137_0229d3a8;
        data_ov137_0229d4a8[1] = data_ov137_0229d3a0;
        data_ov137_0229d4a8[2] = data_ov137_0229d3b0;
        data_ov137_0229d4a8[3] = data_ov137_0229d430;
        data_ov137_0229d4a0 |= 1;
    }

    func_ov137_0229cf0c(self);

    unsigned char idx = self->m_index;
    (self->*data_ov137_0229d4a8[idx])();

    func_ov137_0229cefc(self);
    return 1;
}
