/* func_0206aec4 @ 0x0206aec4, 0xe0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206aec4;
typedef void (UnkStruct_0206aec4::*PMF)();

extern PMF data_020de87c;
extern PMF data_020de974;
extern PMF data_020de96c;
extern PMF data_020de964;
extern PMF data_020de894;
extern PMF data_020de954;
extern PMF data_020de8ac;
extern PMF data_020de944;
extern PMF data_020de8b4;
extern PMF data_020de934;

struct UnkStruct_0206aec4 {
    char pad_00[0x3c];
    int method;
};

extern "C" void func_0206aec4(UnkStruct_0206aec4 *obj)
{
    static PMF tbl[10] = {
        data_020de87c, data_020de974, data_020de96c, data_020de964, data_020de894,
        data_020de954, data_020de8ac, data_020de944, data_020de8b4, data_020de934,
    };

    PMF pmf = tbl[obj->method];
    (obj->*pmf)();
}
