/* func_ov086_02278f80 @ 0x02278f80, 0x44 bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02278f80 {
  public:
    virtual int f();
};

struct Entry {
    int (UnkStruct_02278f80::*pmf)();
    int pad_08[2];
};

extern Entry data_ov086_02279480[];

extern "C" void func_ov086_02278f80(void *obj, int index)
{
    UnkStruct_02278f80 *self = (UnkStruct_02278f80 *) obj;
    int result = 1;
    if (data_ov086_02279480[index].pmf != 0) {
        result = (self->*data_ov086_02279480[index].pmf)();
    }
    if (result != 0) {
        *(int *) ((char *) obj + 0x654) = index;
    }
}
