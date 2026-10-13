/* func_ov054_0226256c @ 0x0226256c, 0x4c bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0226256c {
  public:
    int pad[404];
    int idx;
    virtual int vf0();
    virtual int vf1();
    int nonvirt();
};

struct PmfEntry {
    unsigned int pad[2];
    int (UnkStruct_0226256c::*pmf)();
};

extern PmfEntry data_ov054_022632dc[];

extern "C" int func_ov054_0226256c(UnkStruct_0226256c *p)
{
    int result = 0;
    int index = p->idx;
    if (data_ov054_022632dc[index].pmf != 0) {
        result = (p->*data_ov054_022632dc[index].pmf)();
    }
    return result;
}
