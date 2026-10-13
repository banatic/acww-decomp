/* func_ov088_02278f6c @ 0x02278f6c, 0x44 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern "C" {
class UnkStruct_02278f6c {
  public:
    virtual void f();
    unsigned char pad[0xAC];
    unsigned int idx;
};

typedef void (UnkStruct_02278f6c::*MemFn)();

struct PMFEntry {
    MemFn fn;
    int pad;
};
}

extern unsigned char data_ov088_02279c1c[][12];
extern struct PMFEntry data_ov088_02279c14[];

extern "C" void func_ov088_02278f6c(UnkStruct_02278f6c *obj)
{
    int n = obj->idx;
    if (data_ov088_02279c1c[n][0] == 0) {
        return;
    }
    if (data_ov088_02279c14[n].fn == 0) {
        return;
    }
    (obj->*data_ov088_02279c14[n].fn)();
}
