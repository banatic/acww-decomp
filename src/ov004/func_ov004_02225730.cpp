/* func_ov004_02225730 @ 0x02225730, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02225730;

typedef int (UnkStruct_02225730::*PMF)();

struct GArray1Entry {
    int flag;
    int pad[3];
};

struct GArray2Entry {
    int pad[2];
    PMF pmf;
};

extern GArray1Entry data_ov004_02258198[];
extern GArray2Entry data_ov004_02258190[];

extern "C" int func_ov004_02225730(UnkStruct_02225730 *self)
{
    int result = 0;
    unsigned int field = *(unsigned int *) ((char *) self + 0x654);
    if (data_ov004_02258198[field].flag != 0) {
        result = (self->*data_ov004_02258190[field].pmf)();
    }
    return result;
}
