/* func_ov081_022792e0 @ 0x022792e0, 0x44 bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022792e0 {
  public:
    virtual void vfunc_00();
    char pad_04[0x650];
    int m_field;
};

typedef int (UnkStruct_022792e0::*PMF)();
struct TableEntry {
    PMF pmf;
    int pad_08[2];
};

extern TableEntry data_ov081_022798b4[];

extern "C" void func_ov081_022792e0(UnkStruct_022792e0 *this_ptr, int i)
{
    int result = 1;
    if (data_ov081_022798b4[i].pmf != 0) {
        result = (this_ptr->*data_ov081_022798b4[i].pmf)();
    }
    if (result != 0) {
        this_ptr->m_field = i;
    }
}
