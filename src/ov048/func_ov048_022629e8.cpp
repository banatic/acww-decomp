/* func_ov048_022629e8 @ 0x022629e8, 0x9c bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022629e8;
typedef int (UnkStruct_022629e8::*Pmf)();

struct UnkStruct_022629e8 {
    unsigned char pad_00[0xe71];
    unsigned char idx;
};

extern Pmf data_ov048_02263f14;
extern Pmf data_ov048_02263f0c;
extern Pmf data_ov048_02263df4;
extern Pmf data_ov048_02263efc;

extern "C" int func_ov048_022629e8(UnkStruct_022629e8 *self)
{
    static Pmf table[4] = {data_ov048_02263f14, data_ov048_02263f0c, data_ov048_02263df4, data_ov048_02263efc};

    if (self->idx < 4) {
        if ((self->*table[self->idx])()) {
            self->idx++;
        }
    }
    return 1;
}
