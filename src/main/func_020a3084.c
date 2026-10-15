/* func_020a3084 @ 0x020a3084, 0x354 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a3084 {
    char pad_00[0xa1];
    unsigned char state;
    char pad_A2[0xf4 - 0xa2];
    unsigned char arr_f4[4];
    char pad_F8[0xfc - 0xf8];
    unsigned char arr_fc[4];
};

extern void *data_020ccf94;
extern char data_020e3c40[];

extern int func_020740dc(void);
extern int func_02073fdc(int a);
extern void func_02074078(void);
extern int func_020a259c(struct UnkStruct_020a3084 *o, int a);
extern int func_020a01ec(void);
extern void func_020a0f3c(struct UnkStruct_020a3084 *o);
extern void func_020a0eac(struct UnkStruct_020a3084 *o);
extern void func_020a0340(struct UnkStruct_020a3084 *o, unsigned char *p, int a, int b, int c);
extern int func_020a02f4(struct UnkStruct_020a3084 *o);
extern int func_020a0af8(struct UnkStruct_020a3084 *o);
extern int func_020a2450(struct UnkStruct_020a3084 *o, int a);
extern void *func_02090040(int a);
extern void MI_CpuCopy8(void *d, void *s, int n);
extern void func_02090174(void *d);
extern void func_020a2480(struct UnkStruct_020a3084 *o);
extern int func_020a05e8(struct UnkStruct_020a3084 *o, unsigned char *p, int a, int b, int c, int d, int e, int f, int g);
extern int func_02073044(void);
extern int func_020ebf70(void);
extern void func_02073d74(void *g, int a);
extern void func_02073820(void *g);
extern void func_02073770(void *g, int a, int b);
extern int func_02073dd4(void *a, int b);
extern int func_02073918(void *a, int b);
extern int func_02073c90(void *a, int b);
extern int func_020758ac(int a);
extern void func_020750fc(void);
extern void func_020750f4(void);
extern void func_020a1038(struct UnkStruct_020a3084 *o, int a, int b);
extern int func_020a0174(void);
extern int func_020a0848(struct UnkStruct_020a3084 *o, unsigned char *p, int a, int b, int c, int d);
extern void func_020a25cc(struct UnkStruct_020a3084 *o);
extern int func_020682e0(int a);
extern void func_0206844c(int a, unsigned char *p, char *q);
extern void func_020a4e94(struct UnkStruct_020a3084 *o, int a);

void func_020a3084(struct UnkStruct_020a3084 *self)
{
    int ok;
    int i;
    int n;
    void *g;
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
            if (func_020a01ec()) {
                func_020a0f3c(self);
                func_020a0eac(self);
            }
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
            if (func_020a01ec()) {
                if (!func_020a0af8(self)) {
                    return;
                }
                n = func_020a2450(self, 0);
                if (n < 4) {
                    // The second argument is evaluated first.
                    void *q = func_02090040(0);
                    MI_CpuCopy8(func_02090040(n), q, 0x950);
                } else {
                    func_02090174(func_02090040(0));
                }
                for (i = 2; i >= 0; i--) {
                    func_02090174(func_02090040(i + 1));
                }
                func_020a2480(self);
                self->state = 5;
            } else {
                self->state = 5;
            }
            return;

        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            func_020a05e8(self, &self->state, 1, 5, 0x10, 0x16, 4, func_020a01ec() != 0, func_020740dc());
            return;

        case 12:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            if (!(func_02073044(), func_020ebf70())) {
                return;
            }
            if (!func_020a01ec()) {
                func_02073d74(data_020ccf94, 2);
                self->state = 0xe;
            } else {
                self->state = 0xd;
            }
            return;

        case 14:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            g = data_020ccf94;
            func_02073820(g);
            func_02073770(g, 7, 5);
            self->state = 0x1b;
            return;

        case 13:
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
                for (i = 3; i >= 0; i--) {
                    if (func_02073dd4(g, i) && !func_02073918(g, i) && func_02073c90(g, i)) {
                        ok = 0;
                        break;
                    }
                }
            }
            if (!ok) {
                return;
            }
            if (!func_020758ac(func_020740dc())) {
                return;
            }
            self->state = 0xf;
            return;

        case 15:
            if (func_02073fdc(func_020740dc())) {
                func_02074078();
                return;
            }
            ok = 1;
            func_020750fc();
            i = 3;
            g = data_020ccf94;
            for (; i >= 0; i--) {
                if (func_02073dd4(g, i) && !func_02073918(g, i) && !self->arr_f4[i]) {
                    ok = 0;
                    break;
                }
            }
            func_020750f4();
            if (!ok) {
                return;
            }
            func_020a1038(self, 7, 1);
            func_020a0174();
            self->state = 0x1b;
            return;

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
        case 26:
            func_020a0848(self, &self->state, 0x10, 0x16, func_020740dc(), 1);
            return;

        default:
            func_020a25cc(self);
            if (func_020a01ec()) {
                tmp = 6;
                func_0206844c(func_020682e0(0), &tmp, data_020e3c40);
            }
            func_020a4e94(self, 8);
            return;
    }
}
