/* func_0206b164 @ 0x0206b164, 0xc4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class SelfT;
typedef void (SelfT::*PMF)();

class SelfT {
  public:
    unsigned char pad_00[0x3c];
    int unk_3C;
};

extern int data_021cda68;
extern PMF data_021cdbf4[8];
extern PMF data_020dece4;
extern PMF data_020ded04;
extern PMF data_020ded24;
extern PMF data_020ded34;
extern PMF data_020ded44;
extern PMF data_020ded9c;
extern PMF data_020deda4;
extern PMF data_020dedc4;

extern "C" void func_0206b164(SelfT *self)
{
    if ((data_021cda68 & 1) == 0) {
        data_021cdbf4[0] = data_020dece4;
        data_021cdbf4[1] = data_020ded04;
        data_021cdbf4[2] = data_020ded24;
        data_021cdbf4[3] = data_020ded34;
        data_021cdbf4[4] = data_020ded44;
        data_021cdbf4[5] = data_020ded9c;
        data_021cdbf4[6] = data_020deda4;
        data_021cdbf4[7] = data_020dedc4;
        data_021cda68 |= 1;
    }

    {
        PMF pmf = data_021cdbf4[self->unk_3C];
        (self->*pmf)();
    }
}
