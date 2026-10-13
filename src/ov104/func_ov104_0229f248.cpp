/* func_ov104_0229f248 @ 0x0229f248, 0xf4 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229f248 {
  public:
    unsigned char data[0x8c];
    unsigned char idx;
};

typedef void (UnkStruct_0229f248::*PMF)();

extern PMF data_ov104_0229f668;
extern PMF data_ov104_0229f6c0;
extern PMF data_ov104_0229f6b8;
extern PMF data_ov104_0229f6b0;
extern PMF data_ov104_0229f6a8;
extern PMF data_ov104_0229f6a0;
extern PMF data_ov104_0229f698;
extern PMF data_ov104_0229f690;
extern PMF data_ov104_0229f688;
extern PMF data_ov104_0229f680;
extern PMF data_ov104_0229f678;

extern "C" void func_ov104_0229e9f8(UnkStruct_0229f248 *self);
extern "C" void func_ov104_0229e9c0(UnkStruct_0229f248 *self);

extern "C" int func_ov104_0229f248(UnkStruct_0229f248 *self)
{
    static PMF table[11] = {data_ov104_0229f668, data_ov104_0229f6c0, data_ov104_0229f6b8, data_ov104_0229f6b0,
                            data_ov104_0229f6a8, data_ov104_0229f6a0, data_ov104_0229f698, data_ov104_0229f690,
                            data_ov104_0229f688, data_ov104_0229f680, data_ov104_0229f678};
    func_ov104_0229e9f8(self);
    (self->*table[self->idx])();
    func_ov104_0229e9c0(self);
    return 1;
}
