/* func_ov112_022a1b80 @ 0x022a1b80, 0x114 bytes, Thumb, module ov112
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022a1b80 {
  public:
    char pad_00[0x8c];
    unsigned char idx;
};

typedef void (UnkStruct_022a1b80::*PMF)();

extern const PMF data_ov112_022a2090;
extern const PMF data_ov112_022a2088;
extern const PMF data_ov112_022a1fe0;
extern const PMF data_ov112_022a2078;
extern const PMF data_ov112_022a2070;
extern const PMF data_ov112_022a2068;
extern const PMF data_ov112_022a2060;
extern const PMF data_ov112_022a2058;
extern const PMF data_ov112_022a2050;
extern const PMF data_ov112_022a2048;
extern const PMF data_ov112_022a1fc0;
extern const PMF data_ov112_022a2038;
extern const PMF data_ov112_022a2030;
extern const PMF data_ov112_022a2028;

extern "C" int func_ov112_022a1b80(UnkStruct_022a1b80 *obj)
{
    static PMF arr[14] = {data_ov112_022a2090, data_ov112_022a2088, data_ov112_022a1fe0, data_ov112_022a2078,
                          data_ov112_022a2070, data_ov112_022a2068, data_ov112_022a2060, data_ov112_022a2058,
                          data_ov112_022a2050, data_ov112_022a2048, data_ov112_022a1fc0, data_ov112_022a2038,
                          data_ov112_022a2030, data_ov112_022a2028};
    (obj->*arr[obj->idx])();
    return 1;
}
