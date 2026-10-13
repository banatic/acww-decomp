/* func_ov048_02261704 @ 0x02261704, 0x44 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261704 {
  public:
    char pad[0xb4];
    int b4;
};

typedef void (UnkStruct_02261704::*PMF)();

struct Flag {
    unsigned char flag;
    char pad[11];
};

struct Entry {
    PMF pmf;
    int pad;
};

extern Flag data_ov048_0226434c[];
extern Entry data_ov048_02264344[];

extern "C" void func_ov048_02261704(UnkStruct_02261704 *obj)
{
    int idx = obj->b4;
    if (data_ov048_0226434c[idx].flag == 0) {
        return;
    }
    Entry &e = data_ov048_02264344[idx];
    if (e.pmf == 0) {
        return;
    }
    (obj->*e.pmf)();
}
