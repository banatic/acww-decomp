/* func_02045e24 @ 0x02045e24, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Pt {
    int x;
    int z;
};
struct UnkStruct_02045e24 {
    int x;
    int y;
};

struct Entry {
    u8 b0 : 3;
    u8 code : 5;
    u8 pad_01[7];
    u16 unk_08;
    u8 pad_0A[6];
};

extern int func_02045cec(void *k, int flag);
extern void func_02045db8(void *p);
extern void func_0204629c(void *p);
extern int func_ov003_02221340(int idx, struct UnkStruct_02045e24 *key);
extern struct Entry data_021c7884[];

void func_02045e24(struct Pt *pt, int flag)
{
    volatile u16 a;
    volatile u16 b;
    volatile u16 w;
    u16 v;
    struct Pt local;
    struct UnkStruct_02045e24 pair;
    int res;

    local.x = pt->x;
    local.z = pt->z;
    res = func_02045cec(&local, flag);
    if (res < 0) {
        return;
    }
    {
        struct Entry *e = &data_021c7884[res];
        w = e->unk_08;
        v = w;
        b = v;
        a = v;
        pair.x = a >> 8;
        pair.y = b & 0xff;
        if (func_ov003_02221340(e->b0, &pair) != 0) {
            return;
        }
        switch (e->code) {
            case 4:
            case 10:
            case 22:
            case 25:
                func_02045db8(e);
                break;
            default:
                func_0204629c(e);
                break;
        }
    }
}
