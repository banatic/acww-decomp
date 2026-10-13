/* func_ov050_02264974 @ 0x02264974, 0x208 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    char pad_00[0x8e];
    short unk_8E;
    char pad_90[0x94 - 0x90];
    short unk_94;
    char pad_96[0x4e8 - 0x96];
    int unk_4E8;
    char pad_4EC[0x658 - 0x4ec];
    char unk_658[0x72c - 0x658];
    u8 unk_72C;
} UnkStruct_02264974;

typedef struct {
    int a;
} UnkStruct_02264974_2;

extern int func_0202ec58(void);
extern int func_02073d90(void *);
extern short *func_0209d358(int, int);
extern int func_020a7278(void);
extern int func_0208602c(void);
extern int func_020860d0(int);
extern void func_02087f08(int);
extern int func_0209dffc(void);
extern void func_02087ef0(int);
extern void func_ov050_02264834(UnkStruct_02264974 *, int);
extern int func_020984e8(void);
extern int func_02099640(int);
extern int func_02099020(int, int);
extern void func_0209ad9c(int, int);
extern int func_0209b4d4(void);
extern void func_02030864(int);
extern void func_ov050_02263640(void *, int);
extern int func_02087ec0(int);
extern void func_020367e4(void *);
extern unsigned int func_0209bd44(int);
extern unsigned int func_0209bba0(int);
extern unsigned int func_0209bc40(int);
extern int func_ov050_022604e0(UnkStruct_02264974 *);
extern int func_ov050_022604f8(UnkStruct_02264974 *);
extern int func_ov050_02260510(UnkStruct_02264974 *);
extern int func_020b65b8(void);
extern int func_0202ea40(UnkStruct_02264974 *, UnkStruct_02264974_2 *, int);

extern void *data_020ccf94;
extern char *data_021c526c;

int func_ov050_02264974(UnkStruct_02264974 *p)
{
    UnkStruct_02264974_2 t;
    int h;
    int a;
    int b;
    int c;

    if (func_0202ec58() == 0) {
        return 0;
    }
    if (func_02073d90(data_020ccf94) != 0 || *func_0209d358(0, 0x4a) != 0) {
        p->unk_4E8 |= 2;
        if (func_020a7278() != 0) {
            func_02087f08(func_020860d0(func_0208602c()));
            if (func_0209dffc() != 0) {
                func_02087ef0(func_020860d0(func_0208602c()));
            }
            p->unk_8E = 0;
            p->unk_94 = 0;
            func_ov050_02264834(p, 0xd);
        } else {
            func_ov050_02264834(p, 8);
        }
        return 1;
    }

    func_02087f08(func_020860d0(func_0208602c()));
    if (func_0209dffc() != 0) {
        func_02087ef0(func_020860d0(func_0208602c()));
    }
    h = func_020860d0(func_0208602c());
    a = func_020984e8();
    b = func_02099640(a);
    if (func_02099020(a, 1) != 0) {
        func_0209ad9c(b, 0);
        c = func_0209b4d4();
        func_02030864(1);
        func_ov050_02263640(p->unk_658, 5);
        func_02087ef0(h);
        if (func_02087ec0(h) != 0) {
            func_020367e4(data_021c526c + 0x2a0);
        }
        if (func_0209bd44(c) != 0 && (func_0209bba0(c) >= 1 || func_0209bc40(c) >= 0xc)) {
            func_ov050_02264834(p, 1);
        } else {
            func_ov050_02264834(p, 0);
        }
        return 1;
    }

    if (func_ov050_022604e0(p) != 0 && func_020b65b8() == 0x1d) {
        func_02087ef0(h);
        func_ov050_02264834(p, 0);
    } else if (func_ov050_022604f8(p) != 0 && func_020b65b8() == 0x1d) {
        func_ov050_02264834(p, 0xa);
    } else if (func_ov050_02260510(p) != 0 && func_020b65b8() == 0) {
        func_02087ef0(h);
        func_ov050_02264834(p, 0);
    } else {
        if (func_020b65b8() != 0x1e) {
            func_02087ef0(h);
        }
        func_ov050_02264834(p, 1);
    }
    func_02030864(0);
    if (func_ov050_02260510(p) != 0) {
        if (func_02087ec0(h) != 0) {
            func_020367e4(data_021c526c + 0x2a0);
        }
        if (func_0202ea40(p, &t, 3) != 0) {
            p->unk_72C = 1;
        }
    }
    return 1;
}
