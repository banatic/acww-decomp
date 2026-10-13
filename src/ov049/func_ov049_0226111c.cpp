/* func_ov049_0226111c @ 0x0226111c, 0x44 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226111c {
  public:
    virtual void f();
    char pad[0xb4];
    unsigned int index;
};

struct PMFEntry {
    void (UnkStruct_0226111c::*pmf)();
    unsigned char flag;
    char pad[3];
};

extern PMFEntry data_ov049_022633b0[];

extern "C" void func_ov049_0226111c(UnkStruct_0226111c *this_)
{
    unsigned int idx = this_->index;
    if (data_ov049_022633b0[idx].flag != 0) {
        if (data_ov049_022633b0[idx].pmf != 0) {
            (this_->*data_ov049_022633b0[idx].pmf)();
        }
    }
}
