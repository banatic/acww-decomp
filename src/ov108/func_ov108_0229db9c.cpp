/* func_ov108_0229db9c @ 0x0229db9c, 0x1a4 bytes, Thumb, module ov108
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229db9c {
  public:
    unsigned char pad_00[0x8d];
    unsigned char idx;
};

typedef void (UnkStruct_0229db9c::*PMF)();

extern PMF data_ov108_0229e058, data_ov108_0229e050, data_ov108_0229e048, data_ov108_0229e040, data_ov108_0229e038,
    data_ov108_0229e030, data_ov108_0229e028, data_ov108_0229e020, data_ov108_0229e018, data_ov108_0229e010,
    data_ov108_0229dfc8, data_ov108_0229e008, data_ov108_0229dff8, data_ov108_0229e068, data_ov108_0229dfe8,
    data_ov108_0229dfe0, data_ov108_0229dfd8, data_ov108_0229dfd0, data_ov108_0229dfc0, data_ov108_0229e060,
    data_ov108_0229dff0, data_ov108_0229dfb0, data_ov108_0229dfa8, data_ov108_0229e080;

extern "C" void func_ov108_0229db9c(UnkStruct_0229db9c *self)
{
    static struct {
        PMF a[16];
        PMF b[8];
    } tbl = {{data_ov108_0229e058, data_ov108_0229e050, data_ov108_0229e048, data_ov108_0229e040, data_ov108_0229e038,
              data_ov108_0229e030, data_ov108_0229e028, data_ov108_0229e020, data_ov108_0229e018, data_ov108_0229e010,
              data_ov108_0229dfc8, data_ov108_0229e008, data_ov108_0229dff8, data_ov108_0229e068, data_ov108_0229dfe8,
              data_ov108_0229dfe0},
             {data_ov108_0229dfd8, data_ov108_0229dfd0, data_ov108_0229dfc0, data_ov108_0229e060, data_ov108_0229dff0,
              data_ov108_0229dfb0, data_ov108_0229dfa8, data_ov108_0229e080}};

    (self->*tbl.a[self->idx])();
}
