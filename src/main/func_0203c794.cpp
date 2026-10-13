/* func_0203c794 @ 0x0203c794, 0x1e8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct UnkStruct_0203c794 {
    virtual int v0();
    virtual int v1();
    virtual int v2();
    virtual int v3();
    virtual int v4();
    virtual int v5();
    virtual int v6();
    virtual int v7();
    virtual int v8();
    virtual int v9();
    virtual int v10();
    virtual int v11();
    virtual int v12();
    virtual int v13();
    virtual int v14();
    virtual int v15();
    virtual int v16();
    virtual int v17();
    virtual int v18();
    virtual int v19();
    virtual int v20();
    virtual int v21();
    virtual int v22();
    virtual int v23();
    virtual int v24();
    virtual int v25();
    virtual int v26();
    virtual int v27();
    virtual int v28();
    virtual int v29();
    virtual int v30();
    virtual int v31();
    virtual int v32();
    virtual int v33();
    virtual int v34();
    virtual int v35();
    virtual int v36();
    virtual int v37();
    virtual int v38();
    virtual int v39();
    virtual int v40();
    virtual int v41();
    virtual int v42();
};

struct UnkStruct_0203c794_2 : UnkStruct_0203c794 {
    u8 pad_04[0x110 - 4];
    int unk_110;
    int unk_114;
    int unk_118;
    u8 pad_11C[0x1c8 - 0x11c];
    u16 unk_1C8;
    u8 pad_1CA[0x1e4 - 0x1ca];
    int unk_1E4;
    int unk_1E8;
    int unk_1EC;
    int unk_1F0;
    int pad_1F4;
    int unk_1F8;
    int unk_1FC;
    int unk_200;
    u8 pad_204[0x21c - 0x204];
    UnkStruct_0203c794 *unk_21C;
};

extern "C" {
extern UnkStruct_0203c794_2 *data_021c67a4;
extern int data_020da718;
extern int data_020da714;

extern void func_0203c5a8(UnkStruct_0203c794_2 *self);
extern int func_0203c0ac(UnkStruct_0203c794_2 *self, int a);
extern int *func_02095794(int a);
extern void func_0203c2d4(UnkStruct_0203c794_2 *self);
extern int func_020b65c4(void);
extern UnkStruct_0203c794 *func_0208258c(int *p);
extern UnkStruct_0203c794 *func_020826a8(int idx);
extern int func_020984e8(void);
extern int func_02099020(int a, int b);
extern int func_020b65b8(void);
extern int func_020b67e8(int a);
extern void func_0203ad68(void);
}

extern "C" int func_0203c794(UnkStruct_0203c794_2 *self)
{
    int k;

    data_021c67a4 = self;
    func_0203c5a8(self);
    self->unk_1EC = 1;
    self->unk_1F0 = 1;
    self->unk_1C8 = 0x1555;
    self->unk_1E4 = 0;
    self->unk_1E8 = 0;
    self->unk_1FC = 0;
    self->unk_1F8 = self->unk_1FC;
    if (func_0203c0ac(self, 0) != 0) {
        int *p = func_02095794(4);
        if (p != 0) {
            self->unk_110 = p[0];
            self->unk_114 = p[1];
            self->unk_118 = p[2];
        }
    }
    func_0203c2d4(self);
    k = func_020b65c4();
    if (k == 9) {
        data_020da718 = 0x1000;
    } else {
        data_020da718 = 0x1800;
    }

    switch (k) {
        case 0x2c: {
            UnkStruct_0203c794 *o = 0;
            int idx;
            int n = data_020da714;
            if (n == 8) {
                o = func_0208258c(&data_020da714);
            } else {
                idx = n + 1;
                if (idx == 8) {
                    idx = 0;
                } else {
                    while (idx != data_020da714) {
                        o = func_020826a8(idx);
                        if (o != 0) {
                            if (o->v42() != 0) {
                                break;
                            }
                        }
                        idx++;
                        if (idx == 8) {
                            idx = 0;
                            break;
                        }
                    }
                }
                data_020da714 = idx;
            }
            if (o != 0) {
                self->unk_21C = o;
                func_0203c0ac(self, 7);
            } else {
                data_020da714 = 8;
                func_0203c0ac(self, 8);
            }
            break;
        }
        case 0x2d:
            func_0203c0ac(self, 9);
            break;
        case 6:
            func_0203c0ac(self, 0xa);
            break;
        case 13:
        case 14:
        case 0x2f:
            func_0203c0ac(self, 0xe);
            break;
        case 12:
            func_0203c0ac(self, 6);
            break;
        case 0: {
            int r = func_020984e8();
            if (r != 0) {
                if (func_02099020(r, 0x23) != 0) {
                    if (func_020b67e8(func_020b65b8()) != 0 || func_020b65b8() == 6) {
                        func_0203c0ac(self, 0xd);
                    }
                }
            }
        } break;
    }

    self->v9();
    self->unk_1FC = self->unk_1F8;
    self->unk_200 = self->unk_1FC;
    func_0203ad68();
    return 1;
}
