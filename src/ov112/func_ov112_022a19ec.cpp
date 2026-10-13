/* func_ov112_022a19ec @ 0x022a19ec, 0x194 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022a19ec {
  public:
    void Func();
};
typedef void (UnkStruct_022a19ec::*PMF)();

extern PMF data_ov112_022a2010, data_ov112_022a2008, data_ov112_022a2000, data_ov112_022a1ff8, data_ov112_022a1f60,
    data_ov112_022a1fe8, data_ov112_022a1f90, data_ov112_022a1fd8, data_ov112_022a1fd0, data_ov112_022a1f88,
    data_ov112_022a1fc8, data_ov112_022a1fb8, data_ov112_022a2020, data_ov112_022a1fa8, data_ov112_022a1fa0,
    data_ov112_022a1ff0;
extern PMF data_ov112_022a1f68, data_ov112_022a1f80, data_ov112_022a2018, data_ov112_022a1fb0, data_ov112_022a1f70,
    data_ov112_022a1f98, data_ov112_022a2040;

struct UnkStruct_022a19ec_2 {
    char pad_00[0x8d];
    unsigned char unk_8D;
};

extern "C" void func_ov112_022a19ec(UnkStruct_022a19ec_2 *obj)
{
    static struct {
        PMF table1[16];
        PMF table2[7];
    } tables = {{data_ov112_022a2010, data_ov112_022a2008, data_ov112_022a2000, data_ov112_022a1ff8, data_ov112_022a1f60,
                 data_ov112_022a1fe8, data_ov112_022a1f90, data_ov112_022a1fd8, data_ov112_022a1fd0, data_ov112_022a1f88,
                 data_ov112_022a1fc8, data_ov112_022a1fb8, data_ov112_022a2020, data_ov112_022a1fa8, data_ov112_022a1fa0,
                 data_ov112_022a1ff0},
                {data_ov112_022a1f68, data_ov112_022a1f80, data_ov112_022a2018, data_ov112_022a1fb0, data_ov112_022a1f70,
                 data_ov112_022a1f98, data_ov112_022a2040}};

    UnkStruct_022a19ec *self = (UnkStruct_022a19ec *) obj;
    (self->*tables.table1[obj->unk_8D])();
}
