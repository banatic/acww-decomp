/* func_0206d1a4 @ 0x0206d1a4, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206d1a4 {
  public:
    char pad_00[0x38];
    int m_index;
};

typedef void (UnkStruct_0206d1a4::*PMF)();

extern PMF __ptmf_null;
extern PMF data_020de86c;
extern PMF data_020deb64;
extern PMF data_021cdeec[16];
extern PMF data_021cdf6c;
extern unsigned int data_021cda48;

extern "C" void func_0206d1a4(UnkStruct_0206d1a4 *self)
{
    PMF pmf;
    if ((data_021cda48 & 1) == 0) {
        PMF def = __ptmf_null;
        data_021cdeec[0] = def;
        data_021cdeec[1] = def;
        data_021cdeec[2] = def;
        data_021cdeec[3] = def;
        data_021cdeec[4] = def;
        data_021cdeec[5] = def;
        data_021cdeec[6] = data_020de86c;
        data_021cdeec[7] = data_020deb64;
        data_021cdeec[8] = def;
        data_021cdeec[9] = def;
        data_021cdeec[10] = def;
        data_021cdeec[11] = def;
        data_021cdeec[12] = def;
        data_021cdeec[13] = def;
        data_021cdeec[14] = def;
        data_021cdeec[15] = def;
        data_021cdf6c = def;
        data_021cda48 |= 1;
    }
    int idx = self->m_index;
    pmf = data_021cdeec[idx];
    if (pmf) {
        (self->*pmf)();
    }
}
