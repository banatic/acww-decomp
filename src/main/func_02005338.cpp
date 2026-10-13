/* func_02005338 @ 0x02005338, 0x124 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_02005338 {
    int x;
    int y;
    int z;
};

struct UnkStruct_02005338_2;
typedef void (UnkStruct_02005338_2::*PMF)(void);

struct UnkStruct_02005338_2 {
    u8 pad_00[0x7f8];
    int unk_7F8;
    u8 pad_7FC[0x822 - 0x7fc];
    u16 unk_822;
    int unk_824;
    int unk_828;
    int unk_82C;
    int unk_830;
    int unk_834;
    int unk_838;
};

extern PMF data_020d747c;
extern PMF data_020d74b4;
extern volatile u8 data_020e54a8;

extern "C" {
extern int func_0200f290(UnkStruct_02005338_2 *, int);
extern void func_ov003_0222462c(u16, UnkStruct_02005338 *, UnkStruct_02005338 *, int, int, int);
extern void func_ov004_02233b10(u16, UnkStruct_02005338 *, UnkStruct_02005338 *, int, int, int);

void func_02005338(UnkStruct_02005338_2 *obj)
{
    static PMF tbl[2] = {data_020d747c, data_020d74b4};
    PMF f;
    UnkStruct_02005338 v1;
    UnkStruct_02005338 v2;
    UnkStruct_02005338 v3;
    UnkStruct_02005338 v4;
    int t;

    f = tbl[obj->unk_7F8];
    (obj->*f)();
    if (func_0200f290(obj, 0xd)) {
        t = (data_020e54a8 == 0);
        if (t == 1) {
            v1.x = obj->unk_824;
            v1.y = obj->unk_828;
            v1.z = obj->unk_82C;
            v2.x = obj->unk_830;
            v2.y = obj->unk_834;
            v2.z = obj->unk_838;
            func_ov003_0222462c(obj->unk_822, &v1, &v2, 0, 0, 0);
        } else {
            v3.x = obj->unk_824;
            v3.y = obj->unk_828;
            v3.z = obj->unk_82C;
            v4.x = obj->unk_830;
            v4.y = obj->unk_834;
            v4.z = obj->unk_838;
            func_ov004_02233b10(obj->unk_822, &v3, &v4, 0, 0, 0);
        }
    }
}
}
