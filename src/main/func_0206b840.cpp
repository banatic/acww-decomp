/* func_0206b840 @ 0x0206b840, 0x124 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0206b840;
typedef void (UnkStruct_0206b840::*PMF)(void);
struct UnkStruct_0206b840 {
    int pad_00[14];
    int unk_38;
};

extern PMF data_020ded94, data_020ded8c, data_020de9cc, data_020ded7c, data_020ded74, data_020ded6c, data_020ded64,
    data_020ded5c, data_020de9b4, data_020ded4c, data_020de9ac, data_020ded3c;
extern PMF __ptmf_null;
extern PMF data_020de99c;

extern int data_021cda98;
extern PMF data_021cdd34[12];

extern "C" void func_0206b840(UnkStruct_0206b840 *obj)
{
    if (!(data_021cda98 & 1)) {
        data_021cdd34[0] = data_020ded94;
        data_021cdd34[1] = data_020ded8c;
        data_021cdd34[2] = data_020de9cc;
        data_021cdd34[3] = data_020ded7c;
        data_021cdd34[4] = data_020ded74;
        data_021cdd34[5] = data_020ded6c;
        data_021cdd34[6] = data_020ded64;
        data_021cdd34[7] = data_020ded5c;
        data_021cdd34[8] = data_020de9b4;
        data_021cdd34[9] = data_020ded4c;
        data_021cdd34[10] = data_020de9ac;
        data_021cdd34[11] = data_020ded3c;
        data_021cda98 |= 1;
    }
    PMF f;
    int idx;

    idx = obj->unk_38;
    f = __ptmf_null;
    if (idx == 0xff) {
        f = data_020de99c;
    } else if (idx < 12) {
        f = data_021cdd34[idx];
    }
    (obj->*f)();
}
