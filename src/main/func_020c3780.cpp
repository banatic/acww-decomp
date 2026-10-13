/* func_020c3780 @ 0x020c3780, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_020c3780;

typedef int (UnkStruct_020c3780::*PMF)();

struct GArray1Entry {
    int flag;
    int pad[3];
};

struct GArray2Entry {
    int pad[2];
    PMF pmf;
};

extern GArray1Entry data_021fbce0[];
extern GArray2Entry data_021fbcd8[];

extern "C" int func_020c3780(UnkStruct_020c3780 *self)
{
    int result = 0;
    unsigned int field = *(unsigned int *) ((char *) self + 0x654);
    if (data_021fbce0[field].flag != 0) {
        result = (self->*data_021fbcd8[field].pmf)();
    }
    return result;
}
