/* activity_link_jobs_2: 13 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_020a4210 @ 0x020a4210, 0x14 bytes, Thumb
 * func_020a3ea4 @ 0x020a3ea4, 0x36c bytes, Thumb
 * func_020a3e74 @ 0x020a3e74, 0x30 bytes, Thumb
 * func_020a3bc0 @ 0x020a3bc0, 0x2b4 bytes, Thumb
 * func_020a3bb4 @ 0x020a3bb4, 0xc bytes, Thumb
 * func_020a3abc @ 0x020a3abc, 0xf8 bytes, Thumb
 * func_020a3a94 @ 0x020a3a94, 0x28 bytes, Thumb
 * func_020a38e0 @ 0x020a38e0, 0x1b4 bytes, Thumb
 * func_020a38d4 @ 0x020a38d4, 0xc bytes, Thumb
 * func_020a35bc @ 0x020a35bc, 0x318 bytes, Thumb
 * func_020a35b0 @ 0x020a35b0, 0xc bytes, Thumb
 * func_020a33e0 @ 0x020a33e0, 0x1d0 bytes, Thumb
 * func_020a33d8 @ 0x020a33d8, 0x8 bytes, Thumb
 */

#include "types.h"

struct UnkStruct_020a3ea4_3 {
    char pad_00[0xa1];
    unsigned char state;
    char pad_A2[0xcc - 0xa2];
    int unk_CC;
    char pad_D0[0xd4 - 0xd0];
    unsigned short unk_D4;
    unsigned char unk_D6;
    unsigned char unk_D7;
    unsigned char unk_D8;
    char pad_D9[0xda - 0xd9];
    unsigned char unk_DA;
    char pad_DB[0xdc - 0xdb];
    unsigned char unk_DC[8];
};

struct UnkStruct_020a3ea4 {
    char pad_00[0x64];
    int unk_64;
    int unk_68;
};

struct UnkStruct_020a3ea4_2 {
    char b[8];
};

struct S3b68 {
    char pad_00[0x10];
    short unk_10;
};

struct UnkStruct_020a3bc0_2 {
    char pad_00[0xa1];
    unsigned char state;
    char pad_A2[0xcc - 0xa2];
    int unk_CC;
    char pad_D0[0xd6 - 0xd0];
    unsigned char unk_D6;
    char pad_D7[0xd8 - 0xd7];
    unsigned char unk_D8;
    unsigned char unk_D9;
    char pad_DA[0xe4 - 0xda];
    unsigned char unk_E4;
};

struct UnkStruct_020a3bc0 {
    char pad_00[0x6c];
    unsigned char unk_6C;
};

typedef struct PtrData {
    u8 pad_00[0x6c];
    u8 unk_6C;
} PtrData;

typedef struct UnkStruct_020a3abc {
    u8 pad_00[0xa1];
    u8 state;
    u8 pad_A2[0xd6 - 0xa2];
    u8 flag_d6;
    u8 pad_D7[0xd8 - 0xd7];
    u8 buf_d8[1];
    u8 pad_D9[0xe4 - 0xd9];
    u8 flag_e4;
} UnkStruct_020a3abc;

typedef struct {
    char pad_00[0x64];
    void *unk_64;
} UnkStruct_020a3a94;

struct UnkStruct_020a38e0_2 {
    char pad_00[0xa1];
    unsigned char state;
    char pad_A2[0xd2 - 0xa2];
    unsigned short unk_D2;
    char pad_D4[0xe5 - 0xd4];
    unsigned char unk_E5;
};

struct UnkStruct_020a38e0 {
    char pad_00[0x64];
    int unk_64;
};

struct UnkStruct_020a35bc_2 {
    char pad_00[0xa1];
    unsigned char state;
    char pad_A2[0xd2 - 0xa2];
    unsigned short unk_D2;
    char pad_D4[0xf4 - 0xd4];
    unsigned char arr_f4[4];
    char pad_F8[0xfc - 0xf8];
    unsigned char arr_fc[4];
};

struct UnkStruct_020a35bc {
    char pad_00[0x6c];
    unsigned char unk_6C;
};

typedef struct UnkStruct_020a33e0 UnkStruct_020a33e0;

struct UnkStruct_020a33e0 {
    char pad_00[0xa1];
    unsigned char unk_A1;
    char pad_A2[0xd2 - 0xa2];
    unsigned short unk_D2;
    char pad_D4[0xe6 - 0xd4];
    unsigned char unk_E6;
};

typedef struct UnkStruct_020a33e0_2 UnkStruct_020a33e0_2;

struct UnkStruct_020a33e0_2 {
    char pad_00[0x64];
    int unk_64;
};

extern void func_020a0284(int a, int b);
extern void func_020b1130(void);
extern struct UnkStruct_020a3ea4 *data_020ccf94;
extern unsigned char data_020e37f8;
extern unsigned char data_021dc7a8[];
extern void *data_021f3c24;
extern int data_021f3b74;
extern struct S3b68 data_021f3b68;
extern unsigned char data_021c75b0;
extern int func_02073fdc(int a);
extern void func_02074078(void);
extern int func_020740dc(void);
extern int func_02075c64(void);
extern int func_02075f3c(unsigned char *p);
extern int func_020a0030(int a);
extern int func_02098420(int a);
extern int func_020a13ac(void);
extern int func_020961a8(int a);
extern void func_020ee470(void *);
extern int func_02075b98(void);
extern int func_020ec260(void);
extern int func_02096284(int a);
extern void *func_0209847c(int a);
extern void MI_CpuCopy8(const void *source, void *destination, unsigned int size);
extern void func_02073de0(struct UnkStruct_020a3ea4 *g, int a, int b);
extern void func_020738f4(struct UnkStruct_020a3ea4 *g, int v);
extern void func_020a7394(int a, int b, int c, int d, int e);
extern void func_020962a4(int a, int b);
extern int func_0209db78(int *p, struct UnkStruct_020a3ea4_2 *q);
extern short func_0209db50(int *p, struct UnkStruct_020a3ea4_2 *q);
extern int func_0204e414(void);
extern void func_0204e4bc(int a);
extern void func_0204e42c(int a);
extern void func_0204d0ac(int a);
extern void func_0204de34(void);
extern void func_0204dde0(void);
extern void func_02075104(int a);
extern void func_0206ea3c(unsigned char *p);
extern void func_020ba37c(void);
extern void func_02073d74(struct UnkStruct_020a3ea4 *g, int a);
extern int func_02075c00(int a);
extern int func_02073044(void);
extern int func_020ebf70(void);
extern int func_ov048_02262ee8(void);
extern int func_020b5e10(void);
extern int func_020b6098(int a, int b);
extern void func_020b5e1c(int a, int b);
extern int func_02097b24(void);
extern void func_0209fbec(void);
extern unsigned char data_021f3c1c;
extern int func_020a6ed0(void);
extern int func_020a6cc4(void);
extern void func_020a0340(struct UnkStruct_020a3bc0_2 *o, unsigned char *p, int a, int b, int c);
extern int func_020760bc(unsigned short m);
extern int func_02077690(int a);
extern int func_02075d40(unsigned short m);
extern int func_02075d9c(unsigned char *p, unsigned short m);
extern int func_020759e0(int a);
extern void func_020a003c(int a, int b);
extern void DC_FlushAll(void);
extern int func_02075fc4(unsigned char *p, unsigned short m);
extern int func_02075b14(unsigned short m);
extern void func_0209fc40(int a);
extern int func_02073d70(PtrData *);
extern int func_02075dcc(void *, u16);
extern int func_020984e8(void);
extern void func_02098ff8(int, int);
extern void func_020a6ec0(void *);
extern int func_020a259c(struct UnkStruct_020a38e0_2 *o, int a);
extern void func_020a02b4(struct UnkStruct_020a38e0_2 *o, unsigned char *p, int a);
extern int func_020a2438(struct UnkStruct_020a38e0_2 *o, int a);
extern void func_020a2480(struct UnkStruct_020a38e0_2 *o);
extern int func_020a03e0(struct UnkStruct_020a38e0_2 *o, unsigned char *p, int a, int b, int c, int d, int e, int f);
extern int func_02073dd4(void *a, int b);
extern int func_02073918(void *a, int b);
extern int func_02073c90(void *a, int b);
extern int func_02075918(void);
extern void func_020a1038(struct UnkStruct_020a38e0_2 *o, unsigned char a, int b);
extern int func_020a0174(void);
extern int func_020a0848(struct UnkStruct_020a38e0_2 *o, unsigned char *p, int a, int b, int c, int d);
extern void func_020a25cc(void *receiver);
extern void func_020a4e94(struct UnkStruct_020a38e0_2 *o, int a);
extern unsigned short func_020740b4(void);
extern void func_020a0fac(struct UnkStruct_020a35bc_2 *o);
extern void func_020a0efc(struct UnkStruct_020a35bc_2 *o);
extern int func_020a02f4(struct UnkStruct_020a35bc_2 *o);
extern int func_020a0af8(struct UnkStruct_020a35bc_2 *o);
extern int func_020a2450(struct UnkStruct_020a35bc_2 *o, int a);
extern void *func_02090040(int a);
extern void func_02090174(void *d);
extern void func_0209fc00(unsigned char a);
extern int func_020a05e8(struct UnkStruct_020a35bc_2 *o, unsigned char *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_020758ac(unsigned short a);
extern unsigned int func_020ec2d4(void);
extern void func_02074d60(int a);
extern int func_02073d90(struct UnkStruct_020a35bc *g);
extern void func_02073820(struct UnkStruct_020a35bc *g);
extern void func_020737f0(struct UnkStruct_020a35bc *g, unsigned char *p, int a);
extern void func_02073770(struct UnkStruct_020a35bc *g, int a, int b);
extern void func_02046830(void);
extern void func_020a6c6c(int a);
extern void func_020a0244(int);

void func_020a4210(int a)
{
    func_020a0284(a, 1);
    func_020b1130();
}

void func_020a3ea4(struct UnkStruct_020a3ea4_3 *self)
{
    struct UnkStruct_020a3ea4 *g;
    struct UnkStruct_020a3ea4_2 buf1;
    struct UnkStruct_020a3ea4_2 buf2;
    int ok;
    int j;
    int n;
    int cnt;
    int zero;
    unsigned short m;
    short tmp;
    int *q;

    switch (self->state) {
        case 0:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_02075c64()) {
                return;
            }
            self->state = 1;
            return;

        case 1:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!self->unk_D4) {
                return;
            }
            self->unk_D8 = 0;
            self->state = 2;
            return;

        case 2:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_02075f3c(&self->unk_D8)) {
                return;
            }
            self->unk_D8 = 0;
            self->state = 3;
            return;

        case 3:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_020a0030(self->unk_CC)) {
                return;
            }
            ok = 1;
            for (j = 3; j >= 0; j--) {
                if (j != 0) {
                    m = (unsigned short) (1 << j);
                    if (m == (m & self->unk_D4) && func_02098420(j + 3) == 0) {
                        ok = 0;
                        break;
                    }
                }
            }
            if (ok) {
                return;
            }
            self->state = 4;
            return;

        case 4:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_020a13ac()) {
                return;
            }
            func_020ee470((void *) func_020961a8(4));
            self->state = 5;
            return;

        case 5:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (func_020961a8(4)) {
                return;
            }
            if (!func_02075b98()) {
                return;
            }
            self->state = 6;
            return;

        case 6:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!self->unk_DA) {
                return;
            }
            n = func_020ec260();
            g = data_020ccf94;
            g->unk_64 = n;
            MI_CpuCopy8(func_0209847c(func_02096284(g->unk_68)), func_0209847c(g->unk_64 + 3), 0x249c);
            data_020e37f8 = (unsigned char) func_02096284(g->unk_68);
            g->unk_68 = n;
            cnt = 0;
            j = 3;
            zero = 0;
            for (; j >= 0; j--) {
                if (self->unk_D4 & (1 << j)) {
                    func_02073de0(g, j, 1);
                    cnt = (unsigned char) (cnt + 1);
                } else {
                    func_02073de0(g, j, zero);
                }
            }
            func_020738f4(g, cnt);
            func_020a7394(n, 0xc, 1, 0, 7);
            func_020962a4(0, self->unk_D7);
            func_020962a4(n, n + 3);
            MI_CpuCopy8(data_021f3c24, data_021dc7a8, 0x173fc);
            MI_CpuCopy8(self->unk_DC, &buf1, 8);
            q = (int *) ((int) &data_021f3b74);
            ok = func_0209db78(q, &buf1);
            MI_CpuCopy8(self->unk_DC, &buf2, 8);
            tmp = func_0209db50(q, &buf2);
            *q = ok;
            data_021f3b68.unk_10 = tmp;
            if (func_0204e414()) {
                func_0204e4bc(func_0204e414());
                func_0204e42c(func_0204e414());
                func_0204d0ac(func_0204e414());
            }
            func_0204de34();
            func_0204dde0();
            func_02075104(4);
            func_0206ea3c((unsigned char *) ((int) data_021dc7a8 + 0x173c0));
            func_020ba37c();
            self->unk_D6 = 1;
            func_02073d74(g, 1);
            self->state = 7;
            return;

        case 7:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_02075c00(func_020740dc())) {
                return;
            }
            self->state = 8;
            return;

        case 8:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!(func_02073044(), func_020ebf70())) {
                return;
            }
            func_02073d74(data_020ccf94, 2);
            if (func_ov048_02262ee8()) {
                func_020b6098(func_020b5e10(), 2);
                func_020b5e1c(func_020b5e10(), 3);
            } else {
                func_020b6098(func_020b5e10(), 0);
                func_020b5e1c(func_020b5e10(), 3);
            }
            data_021c75b0 = 1;
            self->state = 9;
            return;
    }
}

void func_020a3e74(int param)
{
    func_020a0284(param, 1);
    if ((*(unsigned char **) &data_020ccf94)[0x6c] == 1) {
        func_02097b24();
        func_02097b24();
        func_020b1130();
        func_0209fbec();
    }
}

void func_020a3bc0(struct UnkStruct_020a3bc0_2 *self)
{
    struct UnkStruct_020a3bc0 *g;

    switch (self->state) {
        case 0:
            if (func_02073fdc(func_020740dc() | (1 << func_020a6ed0()))) {
                func_02074078();
                return;
            }
            if (!func_020a6cc4()) {
                return;
            }
            self->state = 1;
            return;

        case 1:
        case 2:
            if (func_02073fdc(func_020740dc() | (1 << func_020a6ed0()))) {
                func_02074078();
                return;
            }
            func_020a0340(self, &self->state, 1, 0xd, 0x2f);
            if (self->state <= 2) {
                return;
            }
            func_020a7394(data_021f3c1c, 0xc, 1, 0, 7);
            g = (*(struct UnkStruct_020a3bc0 **) &data_020ccf94);
            func_020738f4((struct UnkStruct_020a3ea4 *) g, (unsigned char) ((unsigned char) (g->unk_6C + 1)));
            func_02073de0((struct UnkStruct_020a3ea4 *) g, data_021f3c1c, 1);
            func_02075104(data_021f3c1c);
            return;

        case 3:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_020760bc((unsigned short) (1 << data_021f3c1c))) {
                return;
            }
            self->state = 4;
            return;

        case 4:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_02077690(data_021f3c1c)) {
                return;
            }
            self->state = 5;
            return;

        case 5:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_02075d40((unsigned short) (1 << data_021f3c1c))) {
                return;
            }
            self->unk_D8 = 0;
            self->state = 6;
            return;

        case 6:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_02075d9c(&self->unk_D8, (unsigned short) (1 << data_021f3c1c))) {
                return;
            }
            self->state = 7;
            return;

        case 7:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_020759e0(data_021f3c1c)) {
                return;
            }
            func_020a003c(self->unk_CC, 1);
            self->unk_D8 = 0;
            self->state = 8;
            return;

        case 8:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_020a0030(self->unk_CC)) {
                return;
            }
            DC_FlushAll();
            if (!func_02075fc4(&self->unk_D8, (unsigned short) (1 << data_021f3c1c))) {
                return;
            }
            self->state = 9;
            return;

        case 9:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!self->unk_D9) {
                return;
            }
            if (!func_02075b14((unsigned short) (1 << data_021f3c1c))) {
                return;
            }
            self->state = 0xa;
            return;

        case 10:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!(func_02073044(), func_020ebf70())) {
                return;
            }
            if (!self->unk_E4) {
                return;
            }
            func_02073d74((struct UnkStruct_020a3ea4 *) ((*(struct UnkStruct_020a3bc0 **) &data_020ccf94)), 2);
            self->unk_D6 = 1;
            func_0209fc40(data_021f3c1c);
            self->state = 0xb;
            return;
    }
}

void func_020a3bb4(void *arg)
{
    func_020a0284((int) arg, 1);
}

void func_020a3abc(UnkStruct_020a3abc *self)
{
    switch (self->state) {
        case 0:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (func_02073d70((*(PtrData **) &data_020ccf94)) == 1) {
                PtrData *p;
                func_020a7394((*(u8 *) &data_021f3c1c), 0xc, 1, 0, 7);
                p = (*(PtrData **) &data_020ccf94);
                func_020738f4((struct UnkStruct_020a3ea4 *) p, (u8) ((u8) (p->unk_6C + 1)));
                func_02073de0((struct UnkStruct_020a3ea4 *) p, (u8) ((*(u8 *) &data_021f3c1c)), 1);
                func_02075104((u8) ((*(u8 *) &data_021f3c1c)));
                self->state = 1;
            }
            break;
        case 1:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (func_02075dcc(self->buf_d8, (u16) (1 << (*(u8 *) &data_021f3c1c)))) {
                self->state = 2;
            }
            break;
        case 2:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if ((func_02073044(), func_020ebf70()) && self->flag_e4) {
                func_02073d74((struct UnkStruct_020a3ea4 *) ((*(PtrData **) &data_020ccf94)), 2);
                self->flag_d6 = 1;
                self->state = 3;
            }
            break;
    }
}

void func_020a3a94(int arg0)
{
    int a;
    int b;
    a = ((int) (func_020a0284(arg0, 0), arg0));
    b = func_020984e8();
    func_02098ff8(b, 2);
    func_020a6ec0((*(UnkStruct_020a3a94 **) &data_020ccf94)->unk_64);
}

void func_020a38e0(struct UnkStruct_020a38e0_2 *self)
{
    switch (self->state) {
        case 0:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_020a259c(self, 0)) {
                return;
            }
            self->unk_D2 = (unsigned short) func_020740b4();
            self->state = 1;
            return;

        case 1:
        case 2:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            func_020a02b4(self, &self->state, 1);
            return;

        case 3:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_020a2438(self, (*(struct UnkStruct_020a38e0 **) &data_020ccf94)->unk_64)) {
                return;
            }
            func_020a2480(self);
            self->state = 4;
            return;

        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            func_020a03e0(self, &self->state, 4, 0xe, 0x14, 1, 0, 1);
            return;

        case 12: {
            int ok;
            int i;
            void *p;
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            ok = 1;
            i = 3;
            p = (*(struct UnkStruct_020a38e0 **) &data_020ccf94);
            for (; i >= 0; i--) {
                if (func_02073dd4(p, i) && !func_02073918(p, i) && func_02073c90(p, i)) {
                    ok = 0;
                    break;
                }
            }
            if (!ok) {
                return;
            }
            if (!func_02075918()) {
                return;
            }
            self->state = 0xd;
            return;
        }

        case 13:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!self->unk_E5) {
                return;
            }
            func_020a1038(self, data_020e37f8, 0);
            data_020e37f8 = 7;
            func_020a0174();
            func_020ba37c();
            self->state = 0x19;
            return;

        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            func_020a0848(self, &self->state, 0xe, 0x14, 1, 1);
            return;

        default:
            func_020a25cc(self);
            func_020a4e94(self, 8);
            return;
    }
}

void func_020a38d4(int a)
{
    func_020a0284(a, 0);
}

void func_020a35bc(struct UnkStruct_020a35bc_2 *self)
{
    int ok;
    int i;
    struct UnkStruct_020a35bc *g;
    int a;
    int b;
    void *p;
    unsigned char tmp;

    switch (self->state) {
        case 0:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_020a259c((struct UnkStruct_020a38e0_2 *) self, 0)) {
                return;
            }
            self->unk_D2 = func_020740b4();
            func_020a0fac(self);
            func_020a0efc(self);
            self->state = 1;
            return;

        case 1:
        case 2:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            func_020a0340((struct UnkStruct_020a3bc0_2 *) self, &self->state, 1, 0x2e, 0x2e);
            return;

        case 3:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_020a02f4(self)) {
                return;
            }
            self->state = 4;
            return;

        case 4:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!func_020a0af8(self)) {
                return;
            }
            a = func_020a6ed0();
            b = func_020a2450(self, a);
            p = func_02090040(a);
            MI_CpuCopy8((const void *) p, func_02090040(b), 0x950);
            func_02090174(p);
            func_020a2480((struct UnkStruct_020a38e0_2 *) self);
            func_0209fc00((unsigned char) a);
            self->state = 5;
            return;

        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            func_020a05e8(self, &self->state, 1, 5, 0xf, 0x15, 4, 1, func_020740dc());
            return;

        case 12:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            ok = 1;
            i = 3;
            g = (*(struct UnkStruct_020a35bc **) &data_020ccf94);
            for (; i >= 0; i--) {
                if (func_02073dd4(g, i) && !func_02073918(g, i) && !self->arr_fc[i]) {
                    ok = 0;
                    break;
                }
            }
            if (ok) {
                if (func_02073c90(g, func_020a6ed0())) {
                    ok = 0;
                }
            }
            if (!ok) {
                return;
            }
            if (!func_020758ac((unsigned short) (1 << func_020a6ed0()))) {
                return;
            }
            self->state = 0xd;
            return;

        case 13:
            if (func_02073fdc(func_020740dc() ^ (unsigned short) (1 << func_020a6ed0()))) {
                func_02074078();
                return;
            }
            if (!(func_02073044(), func_020ebf70()) && func_020ec2d4() > 1) {
                return;
            }
            func_02074d60(func_020a6ed0());
            g = (*(struct UnkStruct_020a35bc **) &data_020ccf94);
            func_02073d74((struct UnkStruct_020a3ea4 *) g, 2);
            if (func_02073d90(g)) {
                tmp = (unsigned char) func_020a6ed0();
                g = (*(struct UnkStruct_020a35bc **) &data_020ccf94);
                func_02073820(g);
                func_020737f0(g, &tmp, 1);
                func_02073770(g, 5, 5);
            }
            self->state = 0xe;
            return;

        case 14:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            ok = 1;
            i = 3;
            g = (*(struct UnkStruct_020a35bc **) &data_020ccf94);
            for (; i >= 0; i--) {
                if (func_02073dd4(g, i) && !func_02073918(g, i) && !self->arr_f4[i]) {
                    ok = 0;
                    break;
                }
            }
            if (!ok) {
                return;
            }
            func_020ba37c();
            g = (*(struct UnkStruct_020a35bc **) &data_020ccf94);
            func_02073820(g);
            func_02073770(g, 7, 5);
            if (g->unk_6C == 1) {
                func_02046830();
            }
            self->state = 0x1a;
            return;

        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
            func_020a0848((struct UnkStruct_020a38e0_2 *) self, &self->state, 0xf, 0x15, func_020740dc(), 1);
            return;

        default:
            func_020a25cc((void *) self);
            func_020a4e94((struct UnkStruct_020a38e0_2 *) self, 0xa);
            return;
    }
}

void func_020a35b0(void *a)
{
    func_020a0284((int) a, 0);
}

void func_020a33e0(UnkStruct_020a33e0 *p)
{
    int ok;
    UnkStruct_020a33e0_2 *g;

    switch (p->unk_A1) {
        case 0:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            if (func_020a259c((struct UnkStruct_020a38e0_2 *) p, 0) == 0) {
                break;
            }
            p->unk_D2 = func_020740b4();
            p->unk_A1 = 1;
            break;
        case 1:
        case 2:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            func_020a02b4((struct UnkStruct_020a38e0_2 *) p, &p->unk_A1, 1);
            break;
        case 3:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            if (func_020a2438((struct UnkStruct_020a38e0_2 *) p, (*(UnkStruct_020a33e0_2 **) &data_020ccf94)->unk_64) == 0) {
                break;
            }
            func_020a2480((struct UnkStruct_020a38e0_2 *) p);
            p->unk_A1 = 4;
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            func_020a03e0((struct UnkStruct_020a38e0_2 *) p, &p->unk_A1, 4, 0xf, 0x15, 1, 1, 1);
            break;
        case 12:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            ok = 1;
            if (func_02073c90((void *) ((*(UnkStruct_020a33e0_2 **) &data_020ccf94)), func_020a6ed0()) != 0) {
                ok = 0;
            }
            if (ok == 0) {
                break;
            }
            if (func_02075918() == 0) {
                break;
            }
            p->unk_A1 = 0xd;
            break;
        case 13:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            if ((func_02073044(), func_020ebf70()) == 0) {
                break;
            }
            if (p->unk_D2 == func_020740b4()) {
                break;
            }
            func_020a6c6c(func_020a6ed0());
            g = (*(UnkStruct_020a33e0_2 **) &data_020ccf94);
            func_02073d74((struct UnkStruct_020a3ea4 *) g, 2);
            func_02073820((struct UnkStruct_020a35bc *) g);
            func_02073770((struct UnkStruct_020a35bc *) g, 6, 0);
            p->unk_A1 = 0xe;
            break;
        case 14:
            if (func_02073fdc(1) != 0) {
                func_02074078();
                break;
            }
            if (p->unk_E6 == 0) {
                break;
            }
            func_020ba37c();
            p->unk_A1 = 0x1a;
            break;
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
            func_020a0848((struct UnkStruct_020a38e0_2 *) p, &p->unk_A1, 0xf, 0x15, 1, 1);
            break;
        default:
            func_020a25cc(p);
            func_020a4e94((struct UnkStruct_020a38e0_2 *) p, 0xa);
            break;
    }
}

void func_020a33d8(int argument0)
{
    func_020a0244((int) argument0);
}
