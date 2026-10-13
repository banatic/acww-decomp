/* func_0206cdbc @ 0x0206cdbc, 0x180 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0206cdbc {
  public:
    void Func();
};
typedef void (UnkStruct_0206cdbc::*PMF)();

extern PMF data_0213dd98;
extern PMF data_020dee04, data_020dee0c, data_020dee14, data_020dee24, data_020dee2c, data_020dee3c, data_020dee44,
    data_020dee54, data_020dee5c, data_020dee6c, data_020dee84, data_020dedfc, data_020dedf4, data_020dedec;
extern PMF data_020dede4, data_020deddc, data_020dedd4, data_020dedcc, data_020de9ec;

struct UnkStruct_0206cdbc_2 {
    char pad_00[0x38];
    int unk_38;
};

extern "C" void func_0206cdbc(UnkStruct_0206cdbc_2 *obj)
{
    static struct {
        PMF table1[16];
        PMF table2[5];
    } tables = {{data_0213dd98, data_020dee04, data_020dee0c, data_0213dd98, data_020dee14, data_020dee24, data_020dee2c,
                 data_020dee3c, data_020dee44, data_020dee54, data_020dee5c, data_020dee6c, data_020dee84, data_020dedfc,
                 data_020dedf4, data_020dedec},
                {data_020dede4, data_020deddc, data_020dedd4, data_020dedcc, data_020de9ec}};

    UnkStruct_0206cdbc *self = (UnkStruct_0206cdbc *) obj;
    PMF pmf = tables.table1[obj->unk_38];
    if (pmf) {
        (self->*pmf)();
    }
}
