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

extern int data_021cda78;
extern PMF data_021cdc84[11];

extern "C" void func_0206b750(SelfT *self)
{
    if (!(data_021cda78 & 1)) {
        data_021cdc84[0] = data_020ded1c;
        data_021cdc84[1] = data_020ded14;
        data_021cdc84[2] = data_020de98c;
        data_021cdc84[3] = data_020de85c;
        data_021cdc84[4] = data_020decfc;
        data_021cdc84[5] = data_020de984;
        data_021cdc84[6] = data_020decec;
        data_021cdc84[7] = data_020de97c;
        data_021cdc84[8] = data_020decdc;
        data_021cdc84[9] = data_020decd4;
        data_021cdc84[10] = data_020deccc;
        data_021cda78 |= 1;
    }
    PMF pmf = data_021cdc84[self->unk_3C];
    (self->*pmf)();
}
