/* func_02021694 @ 0x02021694, 0x108 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    u8 pad_00[0x830];
    int unk_830;
} UnkStruct_02021694;
typedef struct {
    u8 pad_00[0x100];
    UnkStruct_02021694 *unk_100;
} UnkStruct_02021694_2;
typedef struct {
    int unk_00;
    u8 unk_04;
} GS;

extern GS data_020c8a50;
extern int data_020c9010[];
extern u8 data_021e5a2c[];

extern void MI_CpuCopy8(const void *, void *, unsigned int);
extern int func_0203fc78(int, u8 *, int);
extern int func_0207cc54(int, int, int);
extern int func_0207f294(int);
extern void *func_0207cec0(u8 *, int);
extern int func_0208150c(void *);
extern int func_02003704(int);
extern u8 *func_02080a2c(void *);
extern void func_02015e10(UnkStruct_02021694_2 *, int, int);
extern void func_02015ed0(UnkStruct_02021694_2 *, int, int);
extern void func_02015ea0(UnkStruct_02021694_2 *, int, int);

int func_02021694(UnkStruct_02021694_2 *a0, u8 *a1, int *a2, u8 *a3, const void *a5)
{
    int ret;
    u16 mask;
    int cnt;
    int i;
    int r;
    int k;
    int idx;
    void *obj;
    u8 *s;
    u8 buf[8];

    ret = 0;
    mask = 0;
    cnt = 0;
    for (i = 0; i < 14; i++) {
        MI_CpuCopy8(a5, buf, 8);
        if (func_0203fc78(data_020c9010[i], buf, ret) ? 1 : ret) {
            mask |= 1 << i;
            cnt++;
        }
    }
    if (cnt > 0) {
        k = func_0207cc54(mask, cnt, 14);
        r = -1;
        if (k >= 5) {
            if (k <= 12) {
                idx = k - 5;
                if (idx != func_0207f294(a0->unk_100->unk_830)) {
                    obj = func_0207cec0(data_021e5a2c, idx);
                    if (obj != 0) {
                        if (func_02003704(func_0208150c(obj))) {
                            s = func_02080a2c(obj);
                            if (s != 0) {
                                r = 5;
                                func_02015e10(a0, func_0208150c(obj), 0);
                                func_02015ed0(a0, s[0], 1);
                                func_02015ea0(a0, s[1], 2);
                            }
                        }
                    }
                }
            } else {
                r = 6;
            }
        } else {
            r = k;
        }
        if (r != -1) {
            *a2 = r;
            *a1 = data_020c8a50.unk_04;
            *a3 = 0;
            ret = data_020c8a50.unk_00;
        }
    }
    return ret;
}
