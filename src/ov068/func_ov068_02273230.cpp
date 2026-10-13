/* func_ov068_02273230 @ 0x02273230, 0x8c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov068_02278800;
struct UnkStruct_02273230 {
    char pad_00[0x594];
    int unk_594;
};
typedef int (UnkStruct_02273230::*PMF)();
extern PMF data_ov068_02278820[3];
extern PMF data_ov068_022778a4;
extern PMF data_ov068_022778cc;
extern PMF data_ov068_022778c4;

extern "C" int func_ov068_02273230(UnkStruct_02273230 *self, int idx)
{
    if (!(data_ov068_02278800 & 1)) {
        data_ov068_02278820[0] = data_ov068_022778a4;
        data_ov068_02278820[1] = data_ov068_022778cc;
        data_ov068_02278820[2] = data_ov068_022778c4;
        data_ov068_02278800 |= 1;
    }
    if (idx < 3) {
        if ((self->*data_ov068_02278820[idx])()) {
            self->unk_594 = idx;
            return 1;
        }
    }
    return 0;
}
