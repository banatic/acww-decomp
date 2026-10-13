/* func_ov084_02279080 @ 0x02279080, 0x44 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

class UnkStruct_02279080 {
  public:
    virtual ~UnkStruct_02279080();
    unsigned char pad_04[0x650];
    int unk_654;
};

typedef int (UnkStruct_02279080::*PMF)();

struct Entry {
    PMF method;
    int pad_08[2];
};

extern Entry data_ov084_022795a0[];

extern "C" void func_ov084_02279080(UnkStruct_02279080 *p, int idx)
{
    int result = 1;
    if (data_ov084_022795a0[idx].method != 0) {
        result = (p->*data_ov084_022795a0[idx].method)();
    }
    if (result != 0) {
        p->unk_654 = idx;
    }
}
