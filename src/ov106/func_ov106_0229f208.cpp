/* func_ov106_0229f208 @ 0x0229f208, 0xf4 bytes, Thumb, module ov106
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229f208 {
  public:
    unsigned char pad_00[0x8c];
    unsigned char idx;
};

typedef void (UnkStruct_0229f208::*PMF)();

extern PMF data_ov106_0229f678;
extern PMF data_ov106_0229f6d0;
extern PMF data_ov106_0229f6c8;
extern PMF data_ov106_0229f6c0;
extern PMF data_ov106_0229f6b8;
extern PMF data_ov106_0229f6b0;
extern PMF data_ov106_0229f6a8;
extern PMF data_ov106_0229f6a0;
extern PMF data_ov106_0229f698;
extern PMF data_ov106_0229f690;
extern PMF data_ov106_0229f688;

extern "C" void func_ov106_0229e960(UnkStruct_0229f208 *self);
extern "C" void func_ov106_0229e928(UnkStruct_0229f208 *self);

extern "C" int func_ov106_0229f208(UnkStruct_0229f208 *self)
{
    static PMF table[11] = {data_ov106_0229f678, data_ov106_0229f6d0, data_ov106_0229f6c8, data_ov106_0229f6c0,
                            data_ov106_0229f6b8, data_ov106_0229f6b0, data_ov106_0229f6a8, data_ov106_0229f6a0,
                            data_ov106_0229f698, data_ov106_0229f690, data_ov106_0229f688};

    func_ov106_0229e960(self);
    (self->*table[self->idx])();
    func_ov106_0229e928(self);
    return 1;
}
