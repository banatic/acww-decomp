/* func_ov004_022251fc @ 0x022251fc, 0x44 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022251fc {
  public:
    char pad[0xb4];
    int b4;
};

typedef void (UnkStruct_022251fc::*PMF)();

struct Flag {
    unsigned char flag;
    char pad[11];
};

struct Entry {
    PMF pmf;
    int pad;
};

extern Flag data_ov004_02258168[];
extern Entry data_ov004_02258160[];

extern "C" void func_ov004_022251fc(UnkStruct_022251fc *obj)
{
    int idx = obj->b4;
    if (data_ov004_02258168[idx].flag == 0) {
        return;
    }
    Entry &e = data_ov004_02258160[idx];
    if (e.pmf == 0) {
        return;
    }
    (obj->*e.pmf)();
}
