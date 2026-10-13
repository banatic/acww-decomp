/* func_ov048_02262bc8 @ 0x02262bc8, 0x9c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02262bc8 {
  public:
    virtual ~UnkStruct_02262bc8();
    unsigned char pad_04[0xe6d];
    unsigned char state;
    virtual int m0();
    virtual int m1();
    virtual int m2();
    virtual int m3();
};

typedef int (UnkStruct_02262bc8::*PMF)();

extern PMF data_ov048_02263e0c;
extern PMF data_ov048_022640e4;
extern PMF data_ov048_02263d84;
extern PMF data_ov048_02263f3c;

extern "C" int func_ov048_02262bc8(UnkStruct_02262bc8 *self)
{
    static PMF table[4] = {data_ov048_02263e0c, data_ov048_022640e4, data_ov048_02263d84, data_ov048_02263f3c};
    if (self->state < 4) {
        if ((self->*table[self->state])()) {
            self->state++;
        }
    }
    return 1;
}
