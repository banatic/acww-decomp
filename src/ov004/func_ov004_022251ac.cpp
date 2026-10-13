/* func_ov004_022251ac @ 0x022251ac, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_022251ac {
  public:
    unsigned char pad_00[0xb4];
    int unk_B4;
};

typedef void (UnkStruct_022251ac::*PMF)();

struct PMFEntry {
    PMF pmf;
    int pad_08;
};

extern unsigned char data_ov004_02258168[];
extern PMFEntry data_ov004_02258160[];
extern "C" void func_ov004_022251a4(UnkStruct_022251ac *obj, int arg);

extern "C" void func_ov004_022251ac(UnkStruct_022251ac *obj)
{
    int idx = obj->unk_B4;
    int offset = idx * 12;
    if (data_ov004_02258168[offset] != 0) {
        return;
    }
    if (data_ov004_02258160[idx].pmf == 0) {
        return;
    }
    (obj->*data_ov004_02258160[idx].pmf)();
    func_ov004_022251a4(obj, 0);
}
