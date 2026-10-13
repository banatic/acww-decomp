/* func_ov049_02260ec8 @ 0x02260ec8, 0x11c bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

extern int func_0206fc6c(void);
extern void *func_020984e8(void);
extern u32 func_0206fc8c(void);
extern int func_020996b8(void *);
extern int func_02072ba4(int);
extern u32 func_02072b64(int, u32);
extern u16 *func_02099710(void *);
extern u16 *func_020996f8(void *);
extern void func_02095b58(void *);
extern void func_02095b40(void *);
extern void func_02071d8c(int, u8, int, u32, int);
extern void func_0206844c(u32, void *, void *);
extern void *data_ov049_02263298;
struct UnkStruct_02260ec8 {
    u8 pad_00[0x976];
    u8 unk_976;
};
struct UnkStruct_02260ec8_2 {
    u8 pad_00[0x40];
    u32 unk_40;
    u8 pad_44[0x6c];
    struct UnkStruct_02260ec8 *unk_B0;
};
inline u16 inline_fn(u16 *arg0)
{
    return *arg0;
}

void func_ov049_02260ec8(struct UnkStruct_02260ec8_2 *self)
{
    u32 idx;
    u16 r5;
    u16 r4;
    u32 v1;
    u32 v2;
    char buf[8];
    unsigned int flag;
    void *p;
    if (func_0206fc6c()) {
        p = func_020984e8();
        idx = func_0206fc8c();
        idx = func_02072b64(func_02072ba4(func_020996b8(p)), idx);
        func_02071d8c(4, self->unk_B0->unk_976, 9, idx, 1);
        if (idx < 8) {
            r5 = (u16) (idx + 0x12a8);
        } else {
            r5 = 0x12a8;
        }
        if (idx < 8) {
            r4 = (u16) (idx + 0x1429);
        } else {
            r4 = 0x1429;
        }
        v1 = *func_02099710(p);
        v2 = *func_020996f8(p);
        if (r5 == v1) {
            u16 cur = inline_fn(func_02099710(p));
            flag = 0;
            if ((((unsigned int) cur) >= 0x12a8) && (((unsigned int) cur) <= 0x12af)) {
                flag = 1;
            }
            if (flag != 0) {
                *((u16 *) (buf + 2)) = r5;
                func_02095b58(buf + 2);
            }
        }
        if (r4 == v2) {
            u16 cur = inline_fn(func_020996f8(p));
            flag = 0;
            if ((((unsigned int) cur) >= 0x1429) && (((unsigned int) cur) <= 0x1430)) {
                flag = 1;
            }
            if (flag != 0) {
                *((u16 *) (buf + 4)) = r4;
                func_02095b40(buf + 4);
            }
        }
        buf[0] = 0x27;
        func_0206844c(self->unk_40, buf, data_ov049_02263298);
    } else {
        buf[1] = 0x22;
        func_0206844c(self->unk_40, buf + 1, data_ov049_02263298);
    }
}
