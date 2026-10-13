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
extern PMF2 data_0213dd98;
extern PMF2 data_020deb9c;
extern PMF2 data_020de864;
extern PMF2 data_020de8dc;

extern "C" void func_0206d330(SelfT2 *self)
{
    static PMF2 table[12] = {data_020deabc, data_020deac4, data_020de84c, data_0213dd98, data_020deb9c, data_0213dd98,
                             data_0213dd98, data_0213dd98, data_0213dd98, data_0213dd98, data_0213dd98, data_020de864};
    int idx = self->unk_34;
    PMF2 pmf = data_0213dd98;
    if (idx == 0xff) {
        pmf = data_020de8dc;
    } else if (idx < 0xc) {
        pmf = table[idx];
    }
    if (pmf) {
        (self->*pmf)();
    }
}
