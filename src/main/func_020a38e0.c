/* func_020a38e0 @ 0x020a38e0, 0x1b4 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

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
extern struct UnkStruct_020a38e0 *data_020ccf94;
extern unsigned char data_020e37f8;

extern int func_02073fdc(int a);
extern void func_02074078(void);
extern int func_020a259c(struct UnkStruct_020a38e0_2 *o, int a);
extern int func_020740b4(void);
extern int func_020a02b4(struct UnkStruct_020a38e0_2 *o, unsigned char *p, int a);
extern int func_020a2438(struct UnkStruct_020a38e0_2 *o, int a);
extern void func_020a2480(struct UnkStruct_020a38e0_2 *o);
extern int func_020a03e0(struct UnkStruct_020a38e0_2 *o, unsigned char *p, int a, int b, int c, int d, int e, int f);
extern int func_02073dd4(void *a, int b);
extern int func_02073918(void *a, int b);
extern int func_02073c90(void *a, int b);
extern int func_02075918(void);
extern int func_020a1038(struct UnkStruct_020a38e0_2 *o, unsigned char a, int b);
extern void func_020a0174(void);
extern void func_020ba37c(void);
extern int func_020a0848(struct UnkStruct_020a38e0_2 *o, unsigned char *p, int a, int b, int c, int d);
extern void func_020a25cc(struct UnkStruct_020a38e0_2 *o);
extern void func_020a4e94(struct UnkStruct_020a38e0_2 *o, int a);

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
            if (!func_020a2438(self, data_020ccf94->unk_64)) {
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
            p = data_020ccf94;
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
