/* func_ov051_02261270 @ 0x02261270, 0x80 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261270 {
  public:
    char pad[0x654];
    int unk_654;
};

typedef int (UnkStruct_02261270::*PMF)();

struct FlagEntry {
    int flag;
    char pad[12];
};

struct PMFEntry {
    int pad_00;
    int pad_04;
    PMF pmf;
};

extern "C" {
extern FlagEntry data_ov051_02261bb0[];
extern PMFEntry data_ov051_02261ba8[];
extern int func_020e8858(void *);
extern int func_02019c20(int, int, int, int, int, int);
extern unsigned short data_020c80f8;
int func_ov051_02261270(UnkStruct_02261270 *self);
}

extern "C" int func_ov051_02261270(UnkStruct_02261270 *self)
{
    int result = 0;
    int idx = self->unk_654;
    if (data_ov051_02261bb0[idx].flag != 0) {
        result = (self->*data_ov051_02261ba8[idx].pmf)();
    }
    if (func_020e8858((char *) self + 0x71a) == 1) {
        int a = data_020c80f8;
        int b = 0;
        func_02019c20((int) ((char *) self + 0x564), 1, 0x8f, 1, a, b);
    }
    return result;
}
