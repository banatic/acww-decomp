/* func_0206b750 @ 0x0206b750, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class SelfT {
  public:
    void method();
    char pad_00[0x3c];
    int unk_3C;
};

typedef void (SelfT::*PMF)();

extern PMF data_020ded1c;
extern PMF data_020ded14;
extern PMF data_020de98c;
extern PMF data_020de85c;
extern PMF data_020decfc;
extern PMF data_020de984;
extern PMF data_020decec;
extern PMF data_020de97c;
extern PMF data_020decdc;
extern PMF data_020decd4;
extern PMF data_020deccc;

extern "C" void func_0206b750(SelfT *self)
{
    static PMF table[11] = {data_020ded1c, data_020ded14, data_020de98c, data_020de85c, data_020decfc, data_020de984,
                            data_020decec, data_020de97c, data_020decdc, data_020decd4, data_020deccc};
    PMF pmf = table[self->unk_3C];
    (self->*pmf)();
}
