/* house_visitor_4: 2 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_02275c78 @ 0x02275c78, 0xfc bytes, Thumb
 * func_ov068_02275b8c @ 0x02275b8c, 0xec bytes, Thumb
 */

struct UnkStruct_02275c78 {
    char pad_00[0x898];
    int unk_898;
};

typedef int (UnkStruct_02275c78::*Pmf)();

extern Pmf data_ov068_0227804c;
extern Pmf data_ov068_02277fd4;
extern Pmf data_ov068_0227803c;
extern Pmf data_ov068_02278034;
extern Pmf data_ov068_0227802c;
extern Pmf data_ov068_02277fcc;
extern Pmf data_ov068_0227801c;
extern Pmf data_ov068_02278014;
extern Pmf data_ov068_02277ffc;
extern Pmf data_ov068_02278004;
extern Pmf data_ov068_02278024;

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

extern "C" int func_ov068_02275c78(UnkStruct_02275c78 *self, int idx)
{
    static int initialized;
    static Pmf table[11];

    if (!(initialized & 1)) {
        table[0] = data_ov068_0227804c;
        table[1] = data_ov068_02277fd4;
        table[2] = data_ov068_0227803c;
        table[3] = data_ov068_02278034;
        table[4] = data_ov068_0227802c;
        table[5] = data_ov068_02277fcc;
        table[6] = data_ov068_0227801c;
        table[7] = data_ov068_02278014;
        table[8] = data_ov068_02277ffc;
        table[9] = data_ov068_02278004;
        table[10] = data_ov068_02278024;
        initialized |= 1;
    }

    if (idx < 11) {
        if ((self->*table[idx])()) {
            self->unk_898 = idx;
            return 1;
        }
    }
    return 0;
}

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
