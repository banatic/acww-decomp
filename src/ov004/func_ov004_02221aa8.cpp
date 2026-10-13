/* func_ov004_02221aa8 @ 0x02221aa8, 0x4c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02221aa8;

typedef int (UnkStruct_02221aa8::*PMF)();

struct GArray1Entry {
    int flag;
    int pad[3];
};

struct GArray2Entry {
    int pad[2];
    PMF pmf;
};

extern GArray1Entry data_ov004_02257f50[];
extern GArray2Entry data_ov004_02257f48[];

extern "C" int func_ov004_02221aa8(UnkStruct_02221aa8 *self)
{
    int result = 0;
    unsigned int field = *(unsigned int *) ((char *) self + 0x898);
    if (data_ov004_02257f50[field].flag != 0) {
        result = (self->*data_ov004_02257f48[field].pmf)();
    }
    return result;
}
