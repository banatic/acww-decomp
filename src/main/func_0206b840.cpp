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
extern PMF data_0213dd98;
extern PMF data_020de99c;

extern "C" void func_0206b840(UnkStruct_0206b840 *obj)
{
    static PMF tbl[12] = {data_020ded94, data_020ded8c, data_020de9cc, data_020ded7c, data_020ded74, data_020ded6c,
                          data_020ded64, data_020ded5c, data_020de9b4, data_020ded4c, data_020de9ac, data_020ded3c};
    PMF f;
    int idx;

    idx = obj->unk_38;
    f = data_0213dd98;
    if (idx == 0xff) {
        f = data_020de99c;
    } else if (idx < 12) {
        f = tbl[idx];
    }
    (obj->*f)();
}
