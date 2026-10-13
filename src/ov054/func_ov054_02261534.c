/* func_ov054_02261534 @ 0x02261534, 0x178 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_02261534_2 {
    char pad_00[0x808];
    int unk_808;
} UnkStruct_02261534_2;

typedef struct UnkStruct_02261534_3 {
    char pad_00[0x40];
    void *unk_40;
    char pad_44[0xb0 - 0x44];
    UnkStruct_02261534_2 *unk_B0;
    char pad_B4[0xc8 - 0xb4];
    char unk_C8;
} UnkStruct_02261534_3;

typedef struct UnkStruct_02261534 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03;
    u8 buf[0x10];
} UnkStruct_02261534;

extern int func_02074308(void);
extern int func_020ec148(int);
extern int func_020e8840(char *);
extern void func_ov054_02261f44(UnkStruct_02261534_3 *);
extern void func_0206844c(void *, u8 *, int);
extern void func_02068358(void *);
extern void func_02068434(void *);
extern void func_ov054_02261cc4(UnkStruct_02261534_3 *, int);
extern int func_020730c8(void);
extern void **func_020eb92c(int);
extern void func_020641c8(int *);
extern void func_02064170(int *);
extern void func_02064158(int *);
extern void func_020641b0(int *);
extern int func_020eb998(void *);
extern void *func_020eb9c4(void *);
extern void MI_CpuCopy8(void *, u8 *, int);
extern void func_020a8874(int *, u8 *, int);
extern void func_020a8a70(int *, int *, int, int);
extern void func_02068404(void *, int, int *);
extern int func_020eb8d8(void *);
extern char data_ov054_02262fac[];

void func_ov054_02261534(UnkStruct_02261534_3 *this)
{
    UnkStruct_02261534 m;
    int blkA[8];
    int blkB[8];
    void *o = this->unk_40;
    int cnt;
    void **list;
    void *item;
    int arg3;
    int n;
    int code;
    u8 i;

    arg3 = *(int *) (data_ov054_02262fac + 12 * this->unk_B0->unk_808);
    cnt = func_020ec148(func_02074308());
    if (func_020e8840(&this->unk_C8) == 0) {
        func_ov054_02261f44(this);
        m.unk_00 = 0x37;
        func_0206844c(o, &m.unk_00, *(int *) (data_ov054_02262fac + 12 * this->unk_B0->unk_808));
        func_02068358(o);
        func_02068434(o);
        func_ov054_02261cc4(this, 0);
        return;
    }
    if (cnt > 0) {
        list = func_020eb92c(func_020730c8());
        func_020641c8(blkA);
        func_02064170(blkB);
        for (i = 0; i < cnt; i++) {
            item = list[i];
            if (item == 0) {
                continue;
            }
            func_020730c8();
            n = func_020eb998(item);
            if (n != 0xe) {
                continue;
            }
            func_020730c8();
            MI_CpuCopy8(func_020eb9c4(item), m.buf, n);
            if (m.buf[0xd] != 1) {
                continue;
            }
            code = 0x38;
            if (m.buf[0xc] == 0) {
                func_020a8874(blkB, m.buf, 6);
                func_020a8a70(blkA, blkB, 0, 0);
                func_02068404(o, 8, blkA);
                code = 0x39;
            }
            m.unk_01 = (u8) code;
            func_0206844c(o, &m.unk_01, arg3);
            func_020730c8();
            if (func_020eb8d8(item) != 0) {
                func_ov054_02261cc4(this, 0xd);
                break;
            } else {
                func_ov054_02261f44(this);
                m.unk_02 = 0x37;
                func_0206844c(o, &m.unk_02, *(int *) (data_ov054_02262fac + 12 * this->unk_B0->unk_808));
                func_02068358(o);
                func_02068434(o);
                func_ov054_02261cc4(this, 0);
                break;
            }
        }
        func_02064158(blkB);
        func_020641b0(blkA);
    }
}
