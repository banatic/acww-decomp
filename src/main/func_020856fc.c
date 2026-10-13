/* func_020856fc @ 0x020856fc, 0x1b0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct UnkStruct_020856fc_2 {
    u8 unk_00;
    u8 unk_01[3];
    u8 unk_04[5];
    u8 unk_09[0x15];
} UnkStruct_020856fc_2;
typedef struct UnkStruct_020856fc {
    int a, b;
} UnkStruct_020856fc;
typedef struct Gx {
    char pad_00[0x64];
    int unk_64;
} Gx;

extern Gx *data_020ccf94;
extern int data_021e5a2c;
extern UnkStruct_020856fc_2 data_021d213c[];

extern int func_02073dd4(Gx *, int);
extern int func_0207af30(void);
extern void func_020984e8(void);
extern void *func_02099640(void);
extern int func_0209bd44(char *);
extern int func_0209bc40(char *);
extern void func_0209e474(UnkStruct_020856fc *);
extern int func_0209e350(char *, UnkStruct_020856fc *);
extern unsigned int func_0209bba0(char *);
extern int func_0207cf14(int *, char *);
extern int func_0207cf74(void);
extern void func_02077978(u8 *, UnkStruct_020856fc *, int *);
extern void MI_CpuCopy8(u8 *, u16 *, int);
extern void func_020b23c8(void);
extern int func_0207ce98(int *, char *);
extern void func_0207f270(void);
extern void func_02079500(void);
extern void func_020b65b8(void);
extern int func_020b6674(void);
extern void func_0207a7f8(int *);
extern int func_0207915c(void);
extern void func_02003348(int, int, UnkStruct_020856fc *, int, int);

void func_020856fc(int p0)
{
    u16 w[4];
    char *base;
    int idx;
    UnkStruct_020856fc v18;
    UnkStruct_020856fc_2 *e;
    int kind;
    UnkStruct_020856fc a20;
    char *obj;
    int r;
    int a28;
    int n;
    int z;
    int res;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }
    kind = 0x85;
    z = 0;
    a20.a = 0;
    a20.b = 0;
    a28 = 0;
    w[1] = 0;
    w[2] = 0;
    w[3] = 0;
    w[0] = 0xfff1;
    r = func_0207af30();
    if (r == 0xb) {
        func_020984e8();
        base = (char *) func_02099640() + 0xa4;
        obj = base + 0x10;
        res = -1;
        if (func_0209bd44(obj) != 0 && func_0209bc40(obj) == 0x15) {
            v18.a = 0;
            v18.b = 0;
            func_0209e474(&v18);
            n = func_0209e350(base + 0x1c, &v18);
            if (func_0209bba0(obj) == 0) {
                if (n <= 0x1e) {
                    res = func_0207cf14(&data_021e5a2c, base);
                }
            } else if (func_0209bba0(obj) < 4) {
                if (n <= 0x3c) {
                    res = func_0207cf14(&data_021e5a2c, base);
                    if (func_0207cf74() != 0) {
                        e = &data_021d213c[res];
                        if (data_021d213c[res].unk_00 != 0) {
                            func_02077978(e->unk_04, &a20, &a28);
                            MI_CpuCopy8(e->unk_09, &w[2], 2);
                        }
                    }
                } else {
                    func_020b23c8();
                    if (func_0207ce98(&data_021e5a2c, base) != 0) {
                        func_0207f270();
                        func_02079500();
                    }
                }
            }
        }
        if (res != -1) {
            w[0] = (u16) ((res & 0xfff) | 0xe000);
            kind = 0x82;
            z = 1;
        }
    } else if (r == 0xa) {
        func_020b65b8();
        if (func_020b6674() != 0) {
            func_0207a7f8(&data_021e5a2c);
        }
        idx = func_0207915c();
        if (func_0207cf74() != 0) {
            w[0] = (u16) ((idx & 0xfff) | 0xe000);
            kind = 0x87;
            func_020b65b8();
            if (func_020b6674() == 0) {
                e = &data_021d213c[idx];
                if (data_021d213c[idx].unk_00 != 0) {
                    func_02077978(e->unk_04, &a20, &a28);
                    MI_CpuCopy8(e->unk_09, &w[2], 2);
                }
            }
            z = 1;
        }
    }
    if (z != 0) {
        func_02003348(kind, w[0], &a20, 0, p0);
    }
}
