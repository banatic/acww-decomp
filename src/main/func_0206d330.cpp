/* func_0206d330 @ 0x0206d330, 0xf0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class SelfT2 {
  public:
    void method();
    char pad_00[0x34];
    int unk_34;
};

typedef void (SelfT2::*PMF2)();

extern PMF2 data_020deabc;
extern PMF2 data_020deac4;
extern PMF2 data_020de84c;
extern PMF2 __ptmf_null;
extern PMF2 data_020deb9c;
extern PMF2 data_020de864;
extern PMF2 data_020de8dc;

extern int data_021cda54;
extern PMF2 data_021cdd94[12];

extern "C" void func_0206d330(SelfT2 *self)
{
    if (!(data_021cda54 & 1)) {
        data_021cdd94[0] = data_020deabc;
        data_021cdd94[1] = data_020deac4;
        data_021cdd94[2] = data_020de84c;
        data_021cdd94[3] = __ptmf_null;
        data_021cdd94[4] = data_020deb9c;
        data_021cdd94[5] = __ptmf_null;
        data_021cdd94[6] = __ptmf_null;
        data_021cdd94[7] = __ptmf_null;
        data_021cdd94[8] = __ptmf_null;
        data_021cdd94[9] = __ptmf_null;
        data_021cdd94[10] = __ptmf_null;
        data_021cdd94[11] = data_020de864;
        data_021cda54 |= 1;
    }
    int idx = self->unk_34;
    PMF2 pmf = __ptmf_null;
    if (idx == 0xff) {
        pmf = data_020de8dc;
    } else if (idx < 0xc) {
        pmf = data_021cdd94[idx];
    }
    if (pmf) {
        (self->*pmf)();
    }
}
