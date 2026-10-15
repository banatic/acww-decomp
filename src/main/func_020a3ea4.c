/* func_020a3ea4 @ 0x020a3ea4, 0x36c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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
