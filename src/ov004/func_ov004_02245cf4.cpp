/* func_ov004_02245cf4 @ 0x02245cf4, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02245cf4;
typedef void (UnkStruct_02245cf4::*PMF)(void);
struct UnkStruct_02245cf4 {};

struct UnkStruct_02245cf4_2 {
    PMF fn;
    int a, b;
};
extern "C" {
extern UnkStruct_02245cf4_2 data_ov004_0225fe94[];
}

extern "C" void func_ov004_02245cf4(UnkStruct_02245cf4 *self, int i)
{
    if (data_ov004_0225fe94[i].fn != 0) {
        (self->*(data_ov004_0225fe94[i].fn))();
    }
    *(int *) ((char *) self + 0x320) = i;
}
