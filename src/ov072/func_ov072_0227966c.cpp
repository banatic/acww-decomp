/* func_ov072_0227966c @ 0x0227966c, 0x4c bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0227966c {
    unsigned char pad[0x654];
    int unk_654;
};

typedef int (UnkStruct_0227966c::*PMF)();

struct TableEntry1 {
    int flag;
    char pad[12];
};

struct TableEntry2 {
    char pad[8];
    PMF pmf;
};

extern TableEntry1 data_ov072_02279be0[];
extern TableEntry2 data_ov072_02279bd8[];

extern "C" int func_ov072_0227966c(UnkStruct_0227966c *self)
{
    int result = 0;
    int idx = self->unk_654;
    if (data_ov072_02279be0[idx].flag) {
        result = (self->*data_ov072_02279bd8[idx].pmf)();
    }
    return result;
}
