/* func_ov075_02278d54 @ 0x02278d54, 0x50 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_02278d54 {
  public:
    char pad_00[0xb0];
    int index;
};

struct CallEntry {
    int (UnkStruct_02278d54::*pmf)();
    int pad_08; // to make stride 12 bytes
};

struct FlagEntry {
    unsigned char flag;
    char pad_01[11];
};

extern CallEntry data_ov075_02279930[];
extern FlagEntry data_ov075_02279938[];
extern void func_ov075_02278d44(UnkStruct_02278d54 *, int);

void func_ov075_02278d54(UnkStruct_02278d54 *self)
{
    if (data_ov075_02279938[self->index].flag != 0) {
        return;
    }
    if (data_ov075_02279930[self->index].pmf == 0) {
        return;
    }
    (self->*(data_ov075_02279930[self->index].pmf))();
    func_ov075_02278d44(self, 0);
}
}
