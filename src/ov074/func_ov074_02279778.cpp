/* func_ov074_02279778 @ 0x02279778, 0x44 bytes, Thumb, module ov074
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279778 {
  public:
    virtual ~UnkStruct_02279778();
    unsigned char pad[0x650];
    int unk_654;
};

typedef int (UnkStruct_02279778::*PMF)();

struct TableEntry {
    PMF pmf;
    unsigned int pad[2];
};

extern TableEntry data_ov074_02279d9c[];

extern "C" void func_ov074_02279778(UnkStruct_02279778 *obj, int index)
{
    int ret = 1;
    if (data_ov074_02279d9c[index].pmf != 0) {
        ret = (obj->*data_ov074_02279d9c[index].pmf)();
    }
    if (ret != 0) {
        obj->unk_654 = index;
    }
}
