/* func_ov004_0223121c @ 0x0223121c, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0223121c;
typedef void (UnkStruct_0223121c::*PMF)(void);
struct UnkStruct_0223121c {};

struct UnkStruct_0223121c_2 {
    PMF fn;
    int a, b;
};
extern "C" {
extern UnkStruct_0223121c_2 data_ov004_022588d8[];
}

extern "C" void func_ov004_0223121c(UnkStruct_0223121c *self, int i)
{
    if (data_ov004_022588d8[i].fn != 0) {
        (self->*(data_ov004_022588d8[i].fn))();
    }
    *(int *) ((char *) self + 0x638) = i;
}
