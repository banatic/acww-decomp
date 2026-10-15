/* func_020a35bc @ 0x020a35bc, 0x318 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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

extern struct UnkStruct_020a35bc *data_020ccf94;

extern int func_020740dc(void);
extern int func_02073fdc(int a);
extern void func_02074078(void);
extern int func_020a259c(struct UnkStruct_020a35bc_2 *o, int a);
extern unsigned short func_020740b4(void);
extern void func_020a0fac(struct UnkStruct_020a35bc_2 *o);
extern void func_020a0efc(struct UnkStruct_020a35bc_2 *o);
extern void func_020a0340(struct UnkStruct_020a35bc_2 *o, unsigned char *p, int a, int b, int c);
extern int func_020a02f4(struct UnkStruct_020a35bc_2 *o);
extern int func_020a0af8(struct UnkStruct_020a35bc_2 *o);
extern int func_020a6ed0(void);
extern int func_020a2450(struct UnkStruct_020a35bc_2 *o, int a);
extern void *func_02090040(int a);
extern void MI_CpuCopy8(void *d, void *s, int n);
extern void func_02090174(void *d);
extern void func_020a2480(struct UnkStruct_020a35bc_2 *o);
extern void func_0209fc00(unsigned char a);
extern int func_020a05e8(struct UnkStruct_020a35bc_2 *o, unsigned char *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_02073dd4(void *a, int b);
extern int func_02073918(void *a, int b);
extern int func_02073c90(void *a, int b);
extern int func_020758ac(unsigned short a);
extern int func_02073044(void);
extern int func_020ebf70(void);
extern unsigned int func_020ec2d4(void);
extern void func_02074d60(int a);
extern void func_02073d74(struct UnkStruct_020a35bc *g, int a);
extern int func_02073d90(struct UnkStruct_020a35bc *g);
extern void func_02073820(struct UnkStruct_020a35bc *g);
extern void func_020737f0(struct UnkStruct_020a35bc *g, unsigned char *p, int a);
extern void func_02073770(struct UnkStruct_020a35bc *g, int a, int b);
extern void func_020ba37c(void);
extern void func_02046830(void);
extern int func_020a0848(struct UnkStruct_020a35bc_2 *o, unsigned char *p, int a, int b, int c, int d);
extern void func_020a25cc(struct UnkStruct_020a35bc_2 *o);
extern void func_020a4e94(struct UnkStruct_020a35bc_2 *o, int a);

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
            if (!func_020a259c(self, 0)) {
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
            func_020a0340(self, &self->state, 1, 0x2e, 0x2e);
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
            MI_CpuCopy8(p, func_02090040(b), 0x950);
            func_02090174(p);
            func_020a2480(self);
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
            g = data_020ccf94;
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
            g = data_020ccf94;
            func_02073d74(g, 2);
            if (func_02073d90(g)) {
                tmp = (unsigned char) func_020a6ed0();
                g = data_020ccf94;
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
            g = data_020ccf94;
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
            g = data_020ccf94;
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
            func_020a0848(self, &self->state, 0xf, 0x15, func_020740dc(), 1);
            return;

        default:
            func_020a25cc(self);
            func_020a4e94(self, 0xa);
            return;
    }
}
