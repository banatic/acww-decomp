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

extern int data_021cda6c;
extern PMF data_021cdc34[10];

extern "C" void func_0206aec4(UnkStruct_0206aec4 *obj)
{
    if (!(data_021cda6c & 1)) {
        data_021cdc34[0] = data_020de87c;
        data_021cdc34[1] = data_020de974;
        data_021cdc34[2] = data_020de96c;
        data_021cdc34[3] = data_020de964;
        data_021cdc34[4] = data_020de894;
        data_021cdc34[5] = data_020de954;
        data_021cdc34[6] = data_020de8ac;
        data_021cdc34[7] = data_020de944;
        data_021cdc34[8] = data_020de8b4;
        data_021cdc34[9] = data_020de934;
        data_021cda6c |= 1;
    }

    PMF pmf = data_021cdc34[obj->method];
    (obj->*pmf)();
}
