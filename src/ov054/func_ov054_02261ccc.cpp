/* func_ov054_02261ccc @ 0x02261ccc, 0x44 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02261ccc {
  public:
    virtual void method();
};

struct Handler {
    void (UnkStruct_02261ccc::*pfn)();
    unsigned char active;
};

extern Handler data_ov054_02263140[];

extern "C" void func_ov054_02261ccc(UnkStruct_02261ccc *obj)
{
    int idx = *(int *) ((char *) obj + 0xB8);
    if (data_ov054_02263140[idx].active || data_ov054_02263140[idx].pfn == 0) {
        return;
    }
    (obj->*data_ov054_02263140[idx].pfn)();
}
