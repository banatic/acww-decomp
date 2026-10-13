/* func_020a2dec @ 0x020a2dec, 0x290 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020a2dec {
    char pad_00[0xa1];
    unsigned char state;
    char pad_A2[0xe5 - 0xa2];
    unsigned char unk_E5;
    unsigned char unk_E6;
};

struct GG {
    char pad_00[0x64];
    int unk_64;
};

extern void *data_020ccf94;
extern unsigned char data_020e37f8;
extern char data_020e3c40[];

extern int func_02073fdc(int a);
extern void func_02074078(void);
extern int func_020a259c(struct UnkStruct_020a2dec *o, int a);
extern void func_020a02b4(struct UnkStruct_020a2dec *o, unsigned char *p, int a);
extern int func_020a01ec(void);
extern int func_020a2438(struct UnkStruct_020a2dec *o, int a);
extern void func_020a2480(struct UnkStruct_020a2dec *o);
extern void func_020a03e0(struct UnkStruct_020a2dec *o, unsigned char *p, int a, int b, int c, int d, int e, int f);
extern int func_02073044(void);
extern int func_020ebf70(int a);
extern void func_02073d74(void *g, int a);
extern int func_02073dd4(void *a, int b);
extern int func_02073918(void *a, int b);
extern int func_02073c90(void *a, int b);
extern int func_02075918(void);
extern int func_02075848(void);
extern void func_020732b4(void *g, int a);
extern int func_020ec920(int a);
extern void func_020a1038(struct UnkStruct_020a2dec *o, int a, int b);
extern void func_020a0174(void);
extern void func_020a0848(struct UnkStruct_020a2dec *o, unsigned char *p, int a, int b, int c, int d);
extern void func_020a25cc(struct UnkStruct_020a2dec *o);
extern int func_020682e0(int a);
extern void func_0206844c(int a, unsigned char *p, char *q);
extern void func_020a4e94(struct UnkStruct_020a2dec *o, int a);

void func_020a2dec(struct UnkStruct_020a2dec *self)
{
    int ok;
    int fl;
    int i;
    void *g;
    unsigned char tmp;

    switch (self->state) {
        case 0:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_020a259c(self, 0)) {
                return;
            }
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
            if (func_020a01ec()) {
                if (!func_020a2438(self, ((struct GG *) data_020ccf94)->unk_64)) {
                    return;
                }
                func_020a2480(self);
                self->state = 4;
            } else {
                self->state = 4;
            }
            return;

        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            ok = (func_020a01ec() == 0);
            func_020a03e0(self, &self->state, 4, 0x11, 0x17, func_020a01ec() != 0, ok, 1);
            return;

        case 12:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!func_020ebf70(func_02073044())) {
                return;
            }
            if (!func_020a01ec()) {
                self->state = 0xd;
            } else {
                self->state = 0xe;
            }
            return;

        case 13:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!self->unk_E6) {
                return;
            }
            func_02073d74(data_020ccf94, 2);
            self->state = 0x1c;
            return;

        case 14:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            fl = 1;
            i = 3;
            g = data_020ccf94;
            for (; i >= 0; i--) {
                if (func_02073dd4(g, i) && !func_02073918(g, i) && func_02073c90(g, i)) {
                    fl = 0;
                    break;
                }
            }
            if (!fl) {
                return;
            }
            if (!func_02075918()) {
                return;
            }
            self->state = 0xf;
            return;

        case 15:
            if (func_02073fdc(1)) {
                func_02074078();
                return;
            }
            if (!self->unk_E5) {
                return;
            }
            if (!func_02075848()) {
                return;
            }
            func_020732b4(data_020ccf94, 2);
            self->state = 0x10;
            return;

        case 16:
            if (func_020ec920(func_02073044())) {
                return;
            }
            func_020a1038(self, data_020e37f8, 0);
            func_020a0174();
            data_020e37f8 = 7;
            self->state = 0x1c;
            return;

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
        case 27:
            func_020a0848(self, &self->state, 0x11, 0x17, 1, 1);
            return;

        default:
            func_020a25cc(self);
            if (func_020a01ec()) {
                tmp = 6;
                func_0206844c(func_020682e0(0), &tmp, data_020e3c40);
                func_020a4e94(self, 0x11);
            } else {
                func_020a4e94(self, 8);
            }
            return;
    }
}
