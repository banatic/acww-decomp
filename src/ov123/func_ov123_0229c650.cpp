/* func_ov123_0229c650 @ 0x0229c650, 0x104 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c650;
typedef void (UnkStruct_0229c650::*PMF)();

extern PMF data_ov123_0229ce70;
extern PMF data_ov123_0229ce80;
extern PMF data_ov123_0229ced8;
extern PMF data_ov123_0229ce48;
extern PMF data_ov123_0229ce58;
extern PMF data_ov123_0229cf38;
extern PMF data_ov123_0229cec0;
extern PMF data_ov123_0229ce40;
extern PMF data_ov123_0229cf58;
extern PMF data_ov123_0229cf50;
extern PMF data_ov123_0229cf48;
extern PMF data_ov123_0229cf40;

struct UnkStruct_0229c650 {
    char pad_00[0x8c];
    unsigned char index;
};

extern "C" void func_ov123_0229bf64(UnkStruct_0229c650 *self);
extern "C" void func_ov123_0229bf50(UnkStruct_0229c650 *self);

extern "C" int func_ov123_0229c650(UnkStruct_0229c650 *self)
{
    static int guard = 0;
    static PMF pmf_table[12] = {data_ov123_0229ce70, data_ov123_0229ce80, data_ov123_0229ced8, data_ov123_0229ce48,
                                data_ov123_0229ce58, data_ov123_0229cf38, data_ov123_0229cec0, data_ov123_0229ce40,
                                data_ov123_0229cf58, data_ov123_0229cf50, data_ov123_0229cf48, data_ov123_0229cf40};
    func_ov123_0229bf64(self);
    (self->*pmf_table[self->index])();
    func_ov123_0229bf50(self);
    return 1;
}
