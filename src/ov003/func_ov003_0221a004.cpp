/* func_ov003_0221a004 @ 0x0221a004, 0x8c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov003_0223c620;
struct UnkStruct_0221a004 {
    char pad_00[0x3a0];
    int unk_3A0;
};
typedef int (UnkStruct_0221a004::*PMF)();
extern PMF data_ov003_0223c624[3];
extern PMF data_ov003_02238198;
extern PMF data_ov003_022381e8;
extern PMF data_ov003_02238180;

extern "C" int func_ov003_0221a004(UnkStruct_0221a004 *self, int idx)
{
    if (!(data_ov003_0223c620 & 1)) {
        data_ov003_0223c624[0] = data_ov003_02238198;
        data_ov003_0223c624[1] = data_ov003_022381e8;
        data_ov003_0223c624[2] = data_ov003_02238180;
        data_ov003_0223c620 |= 1;
    }
    if (idx < 3) {
        if ((self->*data_ov003_0223c624[idx])()) {
            self->unk_3A0 = idx;
            return 1;
        }
    }
    return 0;
}
