/* func_ov068_0226e8bc @ 0x0226e8bc, 0x4c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226e8bc {
  public:
    virtual int vfunc();
    unsigned char pad_04[0x650];
    unsigned int index;
};

typedef int (UnkStruct_0226e8bc::*PMF)();

typedef struct {
    unsigned int flag;
    unsigned int pad_04;
    PMF pmf;
} PTableEntry;

extern PTableEntry data_ov068_02278660[];
extern PTableEntry data_ov068_02278658[];

extern "C" int func_ov068_0226e8bc(UnkStruct_0226e8bc *obj)
{
    int result = 0;
    unsigned int index = obj->index;
    if (data_ov068_02278660[index].flag != 0) {
        result = (obj->*data_ov068_02278658[index].pmf)();
    }
    return result;
}
