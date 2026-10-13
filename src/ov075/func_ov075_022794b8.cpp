/* func_ov075_022794b8 @ 0x022794b8, 0x44 bytes, Thumb, module ov075
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022794b8 {
  public:
    virtual int method0();
    int pad_04[404];
    int data;
};

struct Entry {
    int (UnkStruct_022794b8::*pmf)();
    int pad_08[2];
};

extern Entry data_ov075_02279b08[];

extern "C" void func_ov075_022794b8(UnkStruct_022794b8 *obj, int index)
{
    int result = 1;
    Entry &e = data_ov075_02279b08[index];
    if (e.pmf) {
        result = (obj->*e.pmf)();
    }
    if (result) {
        obj->data = index;
    }
}
