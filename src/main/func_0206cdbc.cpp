/* func_0206cdbc @ 0x0206cdbc, 0x180 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206cdbc {
  public:
    void Func();
};
typedef void (UnkStruct_0206cdbc::*PMF)();

extern PMF __ptmf_null;
extern PMF data_020dee04, data_020dee0c, data_020dee14, data_020dee24, data_020dee2c, data_020dee3c, data_020dee44,
    data_020dee54, data_020dee5c, data_020dee6c, data_020dee84, data_020dedfc, data_020dedf4, data_020dedec;
extern PMF data_020dede4, data_020deddc, data_020dedd4, data_020dedcc, data_020de9ec;

struct UnkStruct_0206cdbc_2 {
    char pad_00[0x38];
    int unk_38;
};

// The static table's guard and its 21 entries.
extern int data_021cda4c;
extern PMF data_021cdf74[21];

extern "C" void func_0206cdbc(UnkStruct_0206cdbc_2 *obj)
{
    if (!(data_021cda4c & 1)) {
        data_021cdf74[0] = __ptmf_null;
        data_021cdf74[1] = data_020dee04;
        data_021cdf74[2] = data_020dee0c;
        data_021cdf74[3] = __ptmf_null;
        data_021cdf74[4] = data_020dee14;
        data_021cdf74[5] = data_020dee24;
        data_021cdf74[6] = data_020dee2c;
        data_021cdf74[7] = data_020dee3c;
        data_021cdf74[8] = data_020dee44;
        data_021cdf74[9] = data_020dee54;
        data_021cdf74[10] = data_020dee5c;
        data_021cdf74[11] = data_020dee6c;
        data_021cdf74[12] = data_020dee84;
        data_021cdf74[13] = data_020dedfc;
        data_021cdf74[14] = data_020dedf4;
        data_021cdf74[15] = data_020dedec;
        data_021cdf74[16] = data_020dede4;
        data_021cdf74[17] = data_020deddc;
        data_021cdf74[18] = data_020dedd4;
        data_021cdf74[19] = data_020dedcc;
        data_021cdf74[20] = data_020de9ec;
        data_021cda4c |= 1;
    }

    UnkStruct_0206cdbc *self = (UnkStruct_0206cdbc *) obj;
    PMF pmf = data_021cdf74[obj->unk_38];
    if (pmf) {
        (self->*pmf)();
    }
}
