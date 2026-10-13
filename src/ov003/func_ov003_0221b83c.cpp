/* func_ov003_0221b83c @ 0x0221b83c, 0x7c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0221b83c {
    char pad_00[0x2b4];
    int unk_2B4;
    void f0();
    void f1();
    void f2();
};

extern void (UnkStruct_0221b83c::*data_ov003_022383e4)();
extern void (UnkStruct_0221b83c::*data_ov003_022383fc)();
extern void (UnkStruct_0221b83c::*data_ov003_0223840c)();

extern "C" void func_ov003_0221b83c(UnkStruct_0221b83c *p)
{
    static void (UnkStruct_0221b83c::*pmf[3])() = {data_ov003_022383e4, data_ov003_022383fc, data_ov003_0223840c};
    int idx = p->unk_2B4;
    if (idx < 3) {
        (p->*pmf[idx])();
    }
}
