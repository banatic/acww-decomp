/* func_ov068_02266f44 @ 0x02266f44, 0x35c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

struct Vec3 {
    int x;
    int y;
    int z;
};

class UnkStruct_02266f44 {
  public:
    virtual void o0();
    virtual void o1();
    virtual void o2();
    virtual void o3();
    virtual void o4();
    virtual void o5();
    virtual void o6();
    virtual void o7();
    virtual void o8();
    virtual void o9();
    virtual void o10();
    virtual void o11();
    virtual void o12();
    virtual void o13();
    virtual void o14();
    virtual void o15();
    virtual void o16();
    virtual void o17();
    virtual void o18();
    virtual void o19();
    virtual void o20();
    virtual void o21();
    virtual void o22();
    virtual void o23();
    virtual void o24();
    virtual void o25();
    virtual void o26();
    virtual void o27();
    virtual void o28();
    virtual void o29();
    virtual void o30();
    virtual void o31();
    virtual void o32();
    virtual void o33();
    virtual void o34();
    virtual void o35();
};

class UnkStruct_02266f44_2 {
  public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void *v25();
    char pad_04[0x5c - 4];
    Vec3 unk_5C;
    Vec3 unk_68;
    char pad_74[0x560 - 0x74];
    u8 unk_560;
    char pad_561[0x680 - 0x561];
    int unk_680;
    char pad_684[0x8b8 - 0x684];
    int unk_8B8;
    char pad_8BC[0x9f8 - 0x8bc];
    UnkStruct_02266f44 *unk_9F8;
    int unk_9FC;
    char pad_A00[4];
    u8 unk_A04;
    char pad_A05[0xa0c - 0xa05];
    int unk_A0C;
};

extern "C" int func_0201ce18(UnkStruct_02266f44_2 *);
extern "C" UnkStruct_02266f44 *func_0201ce50(UnkStruct_02266f44_2 *);
extern "C" int func_ov068_0226cbe4(int *, int);
extern "C" int func_0201cddc(UnkStruct_02266f44_2 *);
extern "C" int func_ov068_0226cf58(UnkStruct_02266f44_2 *);
extern "C" void func_02079400(void *context);
extern "C" void func_ov068_0226cce8(int *, UnkStruct_02266f44_2 *, int);
extern "C" void func_0202dc3c(int *, UnkStruct_02266f44_2 *, int);
extern "C" int func_0201c2a4(UnkStruct_02266f44_2 *, int);
extern "C" void func_02016108(int *, int);
extern "C" void func_020160d8(int *, UnkStruct_02266f44 *);
extern "C" void func_0207d16c(void *);
extern "C" void func_ov068_0226ccd8(int *);
extern "C" int func_0207f1d8(void *);
extern "C" u8 *func_020800d0(void *);
extern "C" void func_0204f794(Vec3 *, int, int);
extern "C" int func_020791ec(void);
extern "C" int func_0207f294(void *);
extern "C" int func_ov068_0226ccb0(int *, UnkStruct_02266f44_2 *);
extern "C" void func_020793f0(void *context);
extern "C" void func_0203eddc(UnkStruct_02266f44_2 *);
extern "C" void func_0207d0f0(void *, int);
extern "C" void func_0201b6e4(UnkStruct_02266f44_2 *, int, int);

extern "C" void func_ov068_02266f44(UnkStruct_02266f44_2 *self, int kind, int arg)
{
    int n;
    UnkStruct_02266f44 *o;
    int st;
    int a;
    int b;
    u8 *q;

    switch (kind) {
        case 3:
            self->unk_560 = (u8) arg;
            if (func_0201ce18(self) != 0) {
                self->unk_9FC = 1;
                self->unk_9F8 = func_0201ce50(self);
                self->unk_9F8->o35();
            } else if (func_ov068_0226cbe4(&self->unk_8B8, 7) != 0) {
                self->unk_9FC = 2;
            } else if (self->unk_A04 != 0) {
                self->unk_9FC = 0xe;
            } else {
                switch (func_0201cddc(self)) {
                    case 1:
                        self->unk_9FC = 3;
                        break;
                    case 2:
                        self->unk_9FC = 4;
                        break;
                    case 0:
                        self->unk_9FC = 5;
                        break;
                    case 3:
                        self->unk_9FC = 6;
                        break;
                    case 4:
                        self->unk_9FC = 7;
                        break;
                    case 5:
                        self->unk_9FC = 8;
                        break;
                    case 6:
                        self->unk_9FC = 9;
                        break;
                    case 7:
                        self->unk_9FC = 0xa;
                        break;
                    case 8:
                    case 9:
                        self->unk_9FC = 0xb;
                        break;
                    default:
                        self->unk_9FC = 0;
                        break;
                }
            }
            if (self->unk_9FC == 0) {
                int context = func_ov068_0226cf58(self);
                if (context != 0) {
                    func_02079400((void *) context);
                }
            }
            func_ov068_0226cce8(&self->unk_8B8, self, 8);
            break;
        case 1:
            n = 5;
            switch (self->unk_A0C) {
                case 0:
                    n = 0xe;
                    self->unk_9FC = 0xd;
                    break;
                case 1:
                    n = 0x14;
                    self->unk_9FC = 0xf;
                    break;
                case 2:
                    n = 0x16;
                    self->unk_9FC = 0x10;
                    break;
            }
            func_0202dc3c(&self->unk_680, self, self->unk_9FC);
            func_02016108(&self->unk_680, func_0201c2a4(self, 4));
            func_ov068_0226cce8(&self->unk_8B8, self, n);
            break;
        case 0:
            self->unk_560 = (u8) arg;
            func_0202dc3c(&self->unk_680, self, self->unk_9FC);
            func_02016108(&self->unk_680, func_0201c2a4(self, 4));
            o = self->unk_9F8;
            if (o != 0) {
                func_020160d8(&self->unk_680, o);
            }
            func_ov068_0226cce8(&self->unk_8B8, self, 5);
            if (self->unk_9FC == 2) {
                if (self->v25() != 0) {
                    func_0207d16c(self->v25());
                }
            }
            self->unk_9F8 = 0;
            self->unk_9FC = 0;
            break;
        case 5:
            self->unk_560 = (u8) arg;
            func_ov068_0226ccd8(&self->unk_8B8);
            func_ov068_0226cce8(&self->unk_8B8, self, 6);
            break;
        case 8:
            st = self->unk_A0C;
            if (st == 0) {
                n = func_0207f1d8(self->v25());
                q = func_020800d0(self->v25());
                func_0204f794(&self->unk_5C, q[0], q[1]);
                {
                    Vec3 *sp = &self->unk_5C;
                    Vec3 *dp = &self->unk_68;
                    dp->x = sp->x;
                    dp->y = sp->y;
                    dp->z = sp->z;
                }
                a = func_020791ec();
                b = func_0207f294(self->v25());
                if (a == b || (unsigned int) (n - 3) <= 4) {
                    func_ov068_0226cce8(&self->unk_8B8, self, 0xc);
                } else {
                    func_ov068_0226cce8(&self->unk_8B8, self, 3);
                }
                self->unk_A0C = 3;
            } else if (st == 2) {
                func_ov068_0226cce8(&self->unk_8B8, self, 0);
                self->unk_A0C = 3;
            } else if (self->unk_A04 != 0) {
                func_ov068_0226cce8(&self->unk_8B8, self, 0x12);
            } else {
                if (func_ov068_0226ccb0(&self->unk_8B8, self) == 0) {
                    func_ov068_0226cce8(&self->unk_8B8, self, 0);
                }
                int context = func_ov068_0226cf58(self);
                if (context != 0) {
                    func_020793f0((void *) context);
                }
            }
            func_0203eddc(self);
            if (self->v25() != 0) {
                func_0207d0f0(self->v25(), -3);
            }
            break;
        case 4:
            if (self->unk_A04 != 0) {
                func_ov068_0226cce8(&self->unk_8B8, self, 0x12);
            } else {
                if (func_ov068_0226ccb0(&self->unk_8B8, self) == 0) {
                    func_ov068_0226cce8(&self->unk_8B8, self, 0);
                }
            }
            break;
        case 2:
        case 6:
        case 7:
            break;
    }
    func_0201b6e4(self, kind, arg);
}
