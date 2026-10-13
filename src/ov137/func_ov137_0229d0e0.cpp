/* func_ov137_0229d0e0 @ 0x0229d0e0, 0x110 bytes, Thumb, module ov137
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_0229d0e0 {
  public:
    char pad_00[0x8d];
    unsigned char idx;
    void method();
};

typedef void (UnkStruct_0229d0e0::*PMF)();

extern PMF data_ov137_0229d418;
extern PMF data_ov137_0229d410;
extern PMF data_ov137_0229d408;
extern PMF data_ov137_0229d3e0;
extern PMF data_ov137_0229d3f0;
extern PMF data_ov137_0229d3f8;
extern PMF data_ov137_0229d400;
extern PMF data_ov137_0229d420;
extern PMF data_ov137_0229d3d8;
extern PMF data_ov137_0229d3d0;
extern PMF data_ov137_0229d3c8;
extern PMF data_ov137_0229d3c0;
extern PMF data_ov137_0229d3b8;
extern PMF data_ov137_0229d3e8;

extern "C" void func_ov137_0229d0e0(UnkStruct_0229d0e0 *obj)
{
    static PMF pmf_table[14] = {data_ov137_0229d418, data_ov137_0229d410, data_ov137_0229d408, data_ov137_0229d3e0,
                                data_ov137_0229d3f0, data_ov137_0229d3f8, data_ov137_0229d400, data_ov137_0229d420,
                                data_ov137_0229d3d8, data_ov137_0229d3d0, data_ov137_0229d3c8, data_ov137_0229d3c0,
                                data_ov137_0229d3b8, data_ov137_0229d3e8};
    unsigned char idx = *((unsigned char *) obj + 0x8d);
    (obj->*pmf_table[idx])();
}
