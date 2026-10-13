/* func_ov120_0229c11c @ 0x0229c11c, 0xbc bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

extern "C" void func_ov120_0229bc4c(void *);
extern "C" void func_ov120_0229bb80(void *);

class UnkStruct_0229c11c {
  public:
    char pad_00[0x8c];
    unsigned char idx;
};

typedef void (UnkStruct_0229c11c::*PMF)();

extern const PMF data_ov120_0229c5a8;
extern const PMF data_ov120_0229c5b0;
extern const PMF data_ov120_0229c548;
extern const PMF data_ov120_0229c528;
extern const PMF data_ov120_0229c598;
extern const PMF data_ov120_0229c590;
extern const PMF data_ov120_0229c588;

extern "C" int func_ov120_0229c11c(UnkStruct_0229c11c *self)
{
    static PMF table[7] = {data_ov120_0229c5a8, data_ov120_0229c5b0, data_ov120_0229c548, data_ov120_0229c528,
                           data_ov120_0229c598, data_ov120_0229c590, data_ov120_0229c588};
    func_ov120_0229bc4c(self);
    (self->*table[self->idx])();
    func_ov120_0229bb80(self);
    return 1;
}
