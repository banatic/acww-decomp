/* func_ov068_02275c78 @ 0x02275c78, 0xfc bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
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
