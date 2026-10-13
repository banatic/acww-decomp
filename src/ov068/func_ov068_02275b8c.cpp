/* func_ov068_02275b8c @ 0x02275b8c, 0xec bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

struct CObject {
    unsigned char pad_00[0x898];
    int idx;
};

typedef void (CObject::*PMF)();

extern PMF data_ov068_0227806c;
extern PMF data_ov068_02278054;
extern PMF data_ov068_02277fbc;
extern PMF data_ov068_02277fc4;
extern PMF data_ov068_02277fe4;
extern PMF data_ov068_02277ff4;
extern PMF data_ov068_0227800c;
extern PMF data_ov068_02278044;
extern PMF data_ov068_02278074;
extern PMF data_ov068_0227805c;
extern PMF data_ov068_02277fec;

extern "C" void func_ov068_02275b8c(CObject *self)
{
    static PMF tbl[11] = {data_ov068_0227806c, data_ov068_02278054, data_ov068_02277fbc, data_ov068_02277fc4,
                          data_ov068_02277fe4, data_ov068_02277ff4, data_ov068_0227800c, data_ov068_02278044,
                          data_ov068_02278074, data_ov068_0227805c, data_ov068_02277fec};
    int idx = self->idx;
    if (idx >= 11) {
        return;
    }
    (self->*tbl[idx])();
}
