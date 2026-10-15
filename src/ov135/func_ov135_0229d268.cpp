/* func_ov135_0229d268 @ 0x0229d268, 0x12c bytes, Thumb, module ov135
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229d268;
typedef void (UnkStruct_0229d268::*PMF)();
extern const PMF data_ov135_0229d5e8;
extern const PMF data_ov135_0229d5e0;
extern const PMF data_ov135_0229d5d8;
extern const PMF data_ov135_0229d5d0;
extern const PMF data_ov135_0229d5c8;
extern const PMF data_ov135_0229d5a0;
extern const PMF data_ov135_0229d5b0;
extern const PMF data_ov135_0229d5b8;
extern const PMF data_ov135_0229d5c0;
extern const PMF data_ov135_0229d5f8;
extern const PMF data_ov135_0229d598;
extern const PMF data_ov135_0229d590;
extern const PMF data_ov135_0229d588;
extern const PMF data_ov135_0229d580;
extern const PMF data_ov135_0229d578;
extern const PMF data_ov135_0229d5a8;

extern "C" void func_ov135_0229d268(UnkStruct_0229d268 *obj)
{
    static PMF table[16] = {data_ov135_0229d5e8, data_ov135_0229d5e0, data_ov135_0229d5d8, data_ov135_0229d5d0,
                            data_ov135_0229d5c8, data_ov135_0229d5a0, data_ov135_0229d5b0, data_ov135_0229d5b8,
                            data_ov135_0229d5c0, data_ov135_0229d5f8, data_ov135_0229d598, data_ov135_0229d590,
                            data_ov135_0229d588, data_ov135_0229d580, data_ov135_0229d578, data_ov135_0229d5a8};
    (obj->*table[((unsigned char *) obj)[0x8d]])();
}
