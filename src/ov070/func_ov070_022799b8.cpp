/* func_ov070_022799b8 @ 0x022799b8, 0x4c bytes, Thumb, module ov070
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022799b8 {
    unsigned char pad[0x654];
    int unk_654;
};

typedef int (UnkStruct_022799b8::*PMF)();

struct TableEntry1 {
    int flag;
    char pad[12];
};

struct TableEntry2 {
    char pad[8];
    PMF pmf;
};

extern TableEntry1 data_ov070_02279f2c[];
extern TableEntry2 data_ov070_02279f24[];

extern "C" int func_ov070_022799b8(UnkStruct_022799b8 *self)
{
    int result = 0;
    int idx = self->unk_654;
    if (data_ov070_02279f2c[idx].flag) {
        result = (self->*data_ov070_02279f24[idx].pmf)();
    }
    return result;
}
