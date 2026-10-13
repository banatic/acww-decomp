/* func_ov120_0229c044 @ 0x0229c044, 0xd8 bytes, Thumb, module ov120
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0229c044 {
    unsigned char pad_00[0x8d];
    unsigned char idx;
};

typedef void (UnkStruct_0229c044::*PMF)();

extern PMF data_ov120_0229c568;
extern PMF data_ov120_0229c578;
extern PMF data_ov120_0229c5a0;
extern PMF data_ov120_0229c560;
extern PMF data_ov120_0229c520;
extern PMF data_ov120_0229c550;
extern PMF data_ov120_0229c530;
extern PMF data_ov120_0229c538;
extern PMF data_ov120_0229c540;
extern PMF data_ov120_0229c570;

extern "C" void func_ov120_0229c044(UnkStruct_0229c044 *self)
{
    static PMF table[10] = {data_ov120_0229c568, data_ov120_0229c578, data_ov120_0229c5a0, data_ov120_0229c560,
                            data_ov120_0229c520, data_ov120_0229c550, data_ov120_0229c530, data_ov120_0229c538,
                            data_ov120_0229c540, data_ov120_0229c570};
    (self->*table[self->idx])();
}
