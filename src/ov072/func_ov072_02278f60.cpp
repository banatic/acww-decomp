/* func_ov072_02278f60 @ 0x02278f60, 0x44 bytes, Thumb, module ov072
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278f60 {
  public:
    char pad[0xB0];
    int index;
};

struct FlagEntry {
    unsigned char flag;
    char pad[11];
};

struct PMFEntry {
    void (UnkStruct_02278f60::*pmf)();
    int pad_08;
};

extern FlagEntry data_ov072_02279a2c[];
extern PMFEntry data_ov072_02279a24[];

extern "C" void func_ov072_02278f60(UnkStruct_02278f60 *self)
{
    int i = self->index;
    if (data_ov072_02279a2c[i].flag && data_ov072_02279a24[i].pmf) {
        (self->*data_ov072_02279a24[i].pmf)();
    }
}
