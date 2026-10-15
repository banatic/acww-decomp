/* func_020a503c @ 0x020a503c, 0x1d4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_020a503c {
    u8 pad_00[0x54];
    int unk_54;
    u8 pad_58[0xac - 0x58];
    void *unk_AC;
    void *unk_B0;
    void *unk_B4;
    void *unk_B8;
    void *unk_BC;
    void *unk_C0;
    void *unk_C4;
    void *unk_C8;
    void *unk_CC;
};

extern char data_021f3c08;
extern void *data_020ccf94;
extern struct UnkStruct_020a503c *data_021f3c3c;
extern void *data_021fbe94;
extern int data_021f3c38;
extern int data_021f3c24;

extern int func_020b65c4(void);
extern int func_0204e414(void);
extern void func_0204e4bc(int);
extern void func_0204e42c(int);
extern void func_0204d0ac(int);
extern void func_0204de34(void);
extern void func_0204dde0(void);
extern int func_02073d90(void *);
extern void func_020a2548(int *, struct UnkStruct_020a503c *);
extern void *func_020e9948(void *, int);
extern void func_020a1bd0(int);
extern void *func_020a1368(void);
extern int func_02050920(void *, int);
extern int func_0209e5f0(void *);
extern void MI_CpuFill8(void *, int, int);
extern void func_0209e5d8(void *);
extern int func_020a008c(void *);
extern void func_0209fb5c(int);

int func_020a503c(struct UnkStruct_020a503c *o)
{
    void *h;
    int v;

    if (func_020b65c4() == 6) {
        if (func_0204e414() != 0) {
            func_0204e4bc(func_0204e414());
            func_0204e42c(func_0204e414());
            func_0204d0ac(func_0204e414());
        }
        func_0204de34();
        func_0204dde0();
    }
    data_021f3c08 = 0;
    if (func_02073d90(data_020ccf94) && (func_020b65c4() == 0xb || func_020b65c4() == 9)) {
        return 0;
    }
    data_021f3c3c = o;
    func_020a2548(&o->unk_54, o);
    o->unk_AC = data_021fbe94;
    if (func_020b65c4() == 0x2e || func_020b65c4() == 6 || func_020b65c4() == 9 || func_020b65c4() == 0xb) {
        o->unk_B0 = func_020e9948(o->unk_AC, 0x173fc);
        o->unk_B4 = func_020e9948(o->unk_AC, 0x173fc);
        o->unk_C4 = func_020e9948(o->unk_AC, 0xc804);
        func_020a1bd0(2);
        h = func_020a1368();
        v = func_02050920(h, 0xc804);
        if (func_0209e5f0(h) == 0 || v != 0) {
            MI_CpuFill8(h, 0, 0xc804);
        }
        func_0209e5d8(h);
    }
    if (func_020b65c4() == 9) {
        o->unk_BC = func_020e9948(o->unk_AC, 0x249c);
    }
    if (func_020b65c4() == 0x2e) {
        o->unk_B8 = func_020e9948(o->unk_AC, 0x173fc);
        o->unk_C0 = func_020e9948(o->unk_AC, 0x950);
    }
    if ((unsigned int) (data_021f3c38 - 0x14) <= 1) {
        o->unk_C8 = func_020e9948(o->unk_AC, 0x17400);
        o->unk_CC = func_020e9948(o->unk_AC, 0x10cc);
        func_020a008c(o->unk_CC);
    }
    if (data_021f3c38 == 0x14) {
        data_021f3c24 = (int) func_020e9948(o->unk_AC, 0x173fc);
        func_0209fb5c(data_021f3c24 + 0x173f8);
    }
    return 1;
}
