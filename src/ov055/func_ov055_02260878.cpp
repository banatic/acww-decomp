/* func_ov055_02260878 @ 0x02260878, 0x50 bytes, Thumb, module ov055
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02260878 {
  public:
    unsigned char pad_00[0xb4];
    int unk_B4;
};

typedef void (UnkStruct_02260878::*PMF)();

struct PMFEntry {
    PMF pmf;
    int pad_08;
};

extern unsigned char data_ov055_02260f14[];
extern PMFEntry data_ov055_02260f0c[];
extern "C" void func_ov055_02260870(UnkStruct_02260878 *obj, int arg);

extern "C" void func_ov055_02260878(UnkStruct_02260878 *obj)
{
    int idx = obj->unk_B4;
    int offset = idx * 12;
    if (data_ov055_02260f14[offset] != 0) {
        return;
    }
    if (data_ov055_02260f0c[idx].pmf == 0) {
        return;
    }
    (obj->*data_ov055_02260f0c[idx].pmf)();
    func_ov055_02260870(obj, 0);
}
