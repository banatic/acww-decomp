/* func_ov050_02264878 @ 0x02264878, 0x4c bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02264878;

typedef int (UnkStruct_02264878::*PMF)();

struct GArray1Entry {
    int flag;
    int pad[3];
};

struct GArray2Entry {
    int pad[2];
    PMF pmf;
};

extern GArray1Entry data_ov050_02265f10[];
extern GArray2Entry data_ov050_02265f08[];

extern "C" int func_ov050_02264878(UnkStruct_02264878 *self)
{
    int result = 0;
    unsigned int field = *(unsigned int *) ((char *) self + 0x654);
    if (data_ov050_02265f10[field].flag != 0) {
        result = (self->*data_ov050_02265f08[field].pmf)();
    }
    return result;
}
